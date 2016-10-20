//
// Created by awbrenn on 10/18/16.
//

#include "VertexParticle.h"

VertexParticle::VertexParticle(Vector3d Pos, Vector3d Vel) {
  pos = Pos;
  vel = Vel;
  mass = 0.1; // TODO: calculate actual mass
  force = Vector3d(0.0, 0.0, 0.0);
}
