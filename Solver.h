//
// Created by awbrenn on 10/21/16.
//

#ifndef SQUISHYMESH_SOLVER_H
#define SQUISHYMESH_SOLVER_H


#include "SpringyMesh.h"

#define EULER 0
#define RK4 4

class Solver {
  public:
    SpringyMesh *spring_mesh;
    double dt; // timestep (dt for delta time per step)

    Solver (SpringyMesh *spring_mesh, double time_step);
    void addExternalForces();
    void addStrutForces();
    void integrate(void (Solver::*integrator)());
    void eulerIntegration();
    void RK4Integration();
    void update(unsigned int integrator);
};


#endif //SQUISHYMESH_SOLVER_H
