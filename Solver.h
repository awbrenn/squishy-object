//
// Created by awbrenn on 10/21/16.
//

#ifndef SQUISHYMESH_SOLVER_H
#define SQUISHYMESH_SOLVER_H


#include "SpringyMesh.h"

class Solver {
  SpringyMesh *spring_mesh;
  double dt; // timestep (dt for delta time per step)

  Solver (SpringyMesh *spring_mesh, double time_step);
};


#endif //SQUISHYMESH_SOLVER_H
