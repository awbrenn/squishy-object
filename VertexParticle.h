//
// Created by awbrenn on 10/18/16.
//

#ifndef SQUISHYMESH_VERTEXPARTICLE_H
#define SQUISHYMESH_VERTEXPARTICLE_H

#include "Vector.h"

class VertexParticle {
  double mass;
  Vector3d pos; // position of vertex particle
  Vector3d vel; // velocity of vertex particle
  Vector3d force; // force acting on vertex particle
};


#endif //SQUISHYMESH_VERTEXPARTICLE_H
