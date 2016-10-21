//
// Created by awbrenn on 10/18/16.
//

#include "VertexParticle.h"

VertexParticle::VertexParticle(Vector3d Pos, Vector3d Vel, double Mass) {
  pos = Pos;
  vel = Vel;
  mass = Mass;
  force = Vector3d(0.0, 0.0, 0.0);
}
