//
// Created by awbrenn on 10/17/16.
//

#include "Object.h"

Object::Object(std::string obj_filename, std::string frag_shader_filename, std::string vert_shader_filename) {
  shader = new Shader((char *) frag_shader_filename.c_str(), (char *) vert_shader_filename.c_str());
  mesh.loadObj(obj_filename);
}
