//
// Created by awbrenn on 10/20/16.
//

#ifndef SQUISHYMESH_SPRINGYOBJECT_H
#define SQUISHYMESH_SPRINGYOBJECT_H

#include "Object.h"
#include "SpringyMesh.h"

class SpringyObject : public Object {
  public:
    SpringyMesh spring_mesh;

    SpringyObject(std::string obj_filename, std::string frag_shader_filename, std::string vert_shader_filename,
                      double mass, double k, double d, double torsional_k, double torsional_d);
};


#endif //SQUISHYMESH_SPRINGYOBJECT_H