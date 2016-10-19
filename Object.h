//
// Created by awbrenn on 10/17/16.
//

#ifndef SQUISHYMESH_OBJECT_H
#define SQUISHYMESH_OBJECT_H
#include "Mesh.h"
#include "Shader.h"

class Object {
  public:
    Mesh mesh;
    Shader* shader;

    Object(std::string obj_filename, std::string frag_shader_filename, std::string vert_shader_filename);
};


#endif //SQUISHYMESH_OBJECT_H
