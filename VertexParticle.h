//
// Created by awbrenn on 10/18/16.
//

#ifndef SQUISHYMESH_VERTEXPARTICLE_H
#define SQUISHYMESH_VERTEXPARTICLE_H

#include "Vector.h"

class VertexParticle {
  public:
    double mass;
    Vector3d pos; // position of vertex particle
    Vector3d vel; // velocity of vertex particle
    Vector3d force; // force acting on vertex particle

  public:
    VertexParticle(Vector3d pos, Vector3d vel, double mass);
};


#endif //SQUISHYMESH_VERTEXPARTICLE_H
