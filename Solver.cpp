//
// Created by awbrenn on 10/21/16.
//

#include "Solver.h"

Solver::Solver(SpringyMesh *Spring_mesh, double time_step) {
  spring_mesh = Spring_mesh;
  dt = time_step;
}

void Solver::addExternalForces() {
  Vector3d gravity(0.0, -9.8, 0.0);
  for (auto vp = spring_mesh->vparticles.begin(); vp < spring_mesh->vparticles.end(); ++vp) {
    vp->force = gravity * vp->mass;
  }
}

void Solver::addStrutForces() {
  for(auto s = spring_mesh->struts.begin(); s < spring_mesh->struts.end(); ++s) {
    VertexParticle* vp1 = &spring_mesh->vparticles[s->v1];
    VertexParticle* vp2 = &spring_mesh->vparticles[s->v2];

    double strut_len = (vp2->pos - vp1->pos).norm();
    Vector3d strut_unit_vector = (vp2->pos - vp1->pos).normalize();

    // calculate spring force
    Vector3d spring_force = (s->k * (strut_len - s->l0) * strut_unit_vector);
    vp1->force = vp1->force + spring_force;
    vp2->force = vp2->force + (-1.0 * spring_force);

    // calculate damper force
    Vector3d damper_force = (s->d * ((vp2->vel - vp1->vel) * strut_unit_vector) * strut_unit_vector);
    vp1->force = vp1->force + damper_force;
    vp2->force = vp2->force + (-1.0 * damper_force);

    // calculate torsional forces if the strut has two faces
    if (s->f1 != UNASSIGNED and s->f2 != UNASSIGNED) {
      Vector3d hinge; // hinge vector
      double angle;
      double torsional_spring_constant = 20.0; // TODO put this in settings
      double torsional_damper_constant = 10.0; // TODO put this in settings
      Vector3d torsional_force;
      Vector3d rot_axis_left; // rotation axis of left face
      Vector3d rot_axis_right; // rotation axis of right face
      Vector3d face_normal_left; // normal of face 1
      Vector3d face_normal_right; // normal of face 2
      std::vector<unsigned int> unshared_vertices; // the vertices that are not shared by the two: stored (left, right)

      // get all the vertices needed for calculations
      VertexParticle* x0;
      VertexParticle* x1;
      VertexParticle* x2;
      VertexParticle* x3;

      // get the vertices not shared by either face
      unshared_vertices = spring_mesh->getUnsharedVertices((unsigned int) s->f1, (unsigned int) s->f2);

      x0 = &spring_mesh->vparticles[s->v1];
      x1 = &spring_mesh->vparticles[s->v2];
      x2 = &spring_mesh->vparticles[unshared_vertices[0]];
      x3 = &spring_mesh->vparticles[unshared_vertices[1]];

      Vector3d x02 = x0->pos - x2->pos;
      Vector3d x03 = x0->pos - x3->pos;

      hinge = (x1->pos - x0->pos).normalize();

      rot_axis_left  = x02 - ((x02 * hinge) * hinge);
      rot_axis_right = x03 - ((x03 * hinge) * hinge);

      face_normal_left = spring_mesh->calculateFaceNormal((unsigned int) s->f1);
      face_normal_right = spring_mesh->calculateFaceNormal((unsigned int) s->f2);

      angle = atan2((face_normal_left % face_normal_right) * hinge, face_normal_left * face_normal_right);

//      if (angle != angle) {
//        std::cout << "Danger will robinson" << std::endl;
//      }

      // calculate the velocity of the points relative to the hinge they are rotating around
      Vector3d hinge_velocity_left;
      Vector3d hinge_velocity_right;
      Vector3d d02 = x02 * hinge;
      Vector3d d03 = x03 * hinge;
      double l01 = (x1->pos - x0->pos).norm();
      double fraction_vel_left = d02.norm() / l01;
      double fraction_vel_right = d03.norm() / l01;

      // bilinearly interpolate to get the relative velocity
      hinge_velocity_left = ((1.0 - fraction_vel_left)  * x0->vel) + (fraction_vel_left  * x1->vel);
      hinge_velocity_right = ((1.0 - fraction_vel_right) * x0->vel) + (fraction_vel_right * x1->vel);

      double rot_speed_left  = ((x2->vel - hinge_velocity_left)  * face_normal_left)  / (rot_axis_left.norm());
      double rot_speed_right = ((x3->vel - hinge_velocity_right) * face_normal_right) / (rot_axis_right.norm());

//      torsional_force = 0.0;
      double spring_force_magnitude = torsional_spring_constant * (angle - s->angle0);
      double damper_force_magnitude = torsional_damper_constant * (rot_speed_left + rot_speed_right);
      torsional_force = (spring_force_magnitude - damper_force_magnitude) * hinge;

      std::cout << "sp: " << spring_force_magnitude << "\td: " << damper_force_magnitude << std::endl;

//      if (torsional_force.norm() > 0) {
//        std::cout << "breakpoint" << std::endl;
//      }

      // calculate the forces on the vertices of the spring
      Vector3d f0;
      Vector3d f1;
      Vector3d f2;
      Vector3d f3;

      f2 = ((torsional_force * hinge) / (rot_axis_left.norm())) * face_normal_left;
      f3 = ((torsional_force * hinge) / (rot_axis_right.norm())) * face_normal_right;

      if (rot_axis_left.norm() == 0) {
        std::cout << "Danger will robinson" << std::endl;
      }
      if (rot_axis_right.norm() == 0) {
        std::cout << "Danger will robinson" << std::endl;
      }

      f1 = -1.0 * (((d02 * f2) + (d03 * f3)) / l01);
      f0 = -1.0 * (f1 + f2 + f3);

//      std::cout << "total:\t"<< f0 + f1 + f2 + f3 << std::endl;

      x0->force = x0->force + f0;
      x1->force = x1->force + f1;
      x2->force = x2->force + f2;
      x3->force = x3->force + f3;
    }
  }
  std::cout << std::endl;
}

// TODO detect geometry collisions rather than ground plane
bool Solver::detectCollision(double *time_step_fraction, Vector3d vp_pos, Vector3d vp_pos_new) {
  bool collision_occurred = false;
  double ground_plane_location = -0.6;

  if (vp_pos.y < ground_plane_location) {
    collision_occurred = true;

    double distance_to_collision = fabs(ground_plane_location - vp_pos.y);
    double total_distance = fabs(vp_pos_new.y - vp_pos.y);

    *time_step_fraction = distance_to_collision / total_distance;
  }

  return collision_occurred;
}


void Solver::eulerIntegration() {
  Vector3d acceleration;
  double time_step_fraction;
  double coefficient_of_restitution = 0.8;
  double coefficient_of_friction = 0.2;

  addExternalForces();
  addStrutForces();


  for (auto vp = spring_mesh->vparticles.begin(); vp < spring_mesh->vparticles.end(); ++vp) {
    acceleration = vp->force / vp->mass;

    Vector3d new_vel = vp->vel + acceleration * dt;
    Vector3d new_pos = vp->pos + vp->vel * dt;

    if (detectCollision(&time_step_fraction, vp->pos, new_pos)) {
      Vector3d plane_normal(0.0, 1.0, 0.0);
      Vector3d collision_vel = vp->vel + (acceleration * (time_step_fraction * dt));
      Vector3d collision_pos = vp->pos + (vp->vel * (time_step_fraction * dt));
      Vector3d normal_vel = (collision_vel * plane_normal) * plane_normal;
      Vector3d tangent_vel = collision_vel - normal_vel;

      new_vel = (-1.0 * coefficient_of_restitution * normal_vel) + ((1.0 - coefficient_of_friction) * tangent_vel);
      vp->vel = new_vel + (acceleration * ((1.0 - time_step_fraction) * dt));
      vp->pos = collision_pos + (new_vel * ((1.0 - time_step_fraction) * dt));
    }
    else {
      vp->vel = new_vel;
      vp->pos = new_pos;
    }
    if (vp->vel.x != vp->vel.x) {
      std::cout << "Danger will robinson" << std::endl;
    }
  }
}

void Solver::RK4Integration() {
  std::cout << "RK4" << std::endl;

}

void Solver::update(unsigned int integrator, Mesh* render_mesh) {
  switch(integrator) {
    case EULER:
      eulerIntegration();
      break;
    case RK4:
      RK4Integration();
      break;
    default:
      RK4Integration();
  }

  // copy the updated geometry to the mesh we will render
  spring_mesh->convertToRenderMesh(render_mesh);


//   Debugging print for vertex normals
//  for(int face_index = 0; face_index < render_mesh->GLfaces.size(); ++face_index) {
//    std::cout << render_mesh->GLfaces[face_index].vn[0].x << " ";
//    std::cout << render_mesh->GLfaces[face_index].vn[0].y << " ";
//    std::cout << render_mesh->GLfaces[face_index].vn[0].z << " ";
//
//    std::cout << std::endl;
//
//    std::cout << render_mesh->GLfaces[face_index].vn[1].x << " ";
//    std::cout << render_mesh->GLfaces[face_index].vn[1].y << " ";
//    std::cout << render_mesh->GLfaces[face_index].vn[1].z << " ";
//
//    std::cout << std::endl;
//
//    std::cout << render_mesh->GLfaces[face_index].vn[2].x << " ";
//    std::cout << render_mesh->GLfaces[face_index].vn[2].y << " ";
//    std::cout << render_mesh->GLfaces[face_index].vn[2].z << " ";
//
//    std::cout << std::endl;
//  }
//  std::cout << std::endl;
//  std::cout << std::endl;
}