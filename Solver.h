//
// Created by awbrenn on 10/21/16.
//

#ifndef SQUISHYMESH_SOLVER_H
#define SQUISHYMESH_SOLVER_H


#include "SpringyMesh.h"

#define EULER 0
#define RK4 4

class Solver {
  private:
    void addExternalForces();
    void addStrutForces();

    bool detectCollision(double *time_step_fraction, Vector3d vp_pos, Vector3d vp_pos_new);
    void eulerIntegration();
    void RK4Integration();

  public:
    SpringyMesh *spring_mesh;
    double dt; // timestep (dt for delta time per step)

    Solver (SpringyMesh *spring_mesh, double time_step);

    void update(unsigned int integrator, Mesh* render_mesh);
};


#endif //SQUISHYMESH_SOLVER_H
