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

}

void Solver::eulerIntegration() {
  Vector3d acceleration;

  addExternalForces();
  for (auto vp = spring_mesh->vparticles.begin(); vp < spring_mesh->vparticles.end(); ++vp) {
    acceleration = vp->force / vp->mass;
    vp->vel = vp->vel + acceleration * dt;
    vp->pos = vp->pos + vp->vel * dt;
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
}