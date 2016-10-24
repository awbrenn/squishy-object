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
  }
}

// TODO detect geometry collisions rather than ground plane
bool Solver::detectCollision(double *time_step_fraction, Vector3d vp_pos, Vector3d vp_pos_new) {
  bool collision_occurred = false;
  double ground_plane_location = -8.0;

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