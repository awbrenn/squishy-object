//
// Created by awbrenn on 10/21/16.
//

#ifndef SQUISHYMESH_SOLVER_H
#define SQUISHYMESH_SOLVER_H


#include "SpringyMesh.h"

#define LEAPFROG 0
#define SIXTH 4

class Solver {
  private:
    void addExternalForces();
    void addStrutForces();
    void addUserForces();

    bool detectCollision(double *time_step_fraction, Vector3d vp_pos, Vector3d vp_pos_new);
    void leapFrog(double time_step);
    void sixth();

  public:
    SpringyMesh *spring_mesh;
    double ground_level;
    double coeff_of_restitution;
    double coeff_of_friction;
    Vector3d user_acceleration;
    double dt; // timestep (dt for delta time per step)

    Solver(SpringyMesh *spring_mesh, double time_step, double ground_level, double coefficient_of_restitution,
               double coefficient_of_friction);

    void update(unsigned int integrator, Mesh *render_mesh, Vector3d user_acceleration);
};


#endif //SQUISHYMESH_SOLVER_H
