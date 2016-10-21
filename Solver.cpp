//
// Created by awbrenn on 10/21/16.
//

#include "Solver.h"

Solver::Solver(SpringyMesh *Spring_mesh, double time_step) {
  spring_mesh = Spring_mesh;
  dt = time_step;
}

void Solver::addExternalForces() {

}

void Solver::addStrutForces() {

}

void Solver::eulerIntegration() {

}

void Solver::RK4Integration() {
  std::cout << "RK4" << std::endl;
}

void Solver::update(unsigned int integrator) {
  switch(integrator) {
    case EULER:
      eulerIntegration();
    case RK4:
      RK4Integration();
    default:
      RK4Integration();
  }
}