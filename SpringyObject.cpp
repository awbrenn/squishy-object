//
// Created by awbrenn on 10/20/16.
//

#include "SpringyObject.h"


SpringyObject::SpringyObject(std::string obj_filename, std::string frag_shader_filename,
                             std::string vert_shader_filename, double mass, double k, double d) :
                             Object(obj_filename, frag_shader_filename, vert_shader_filename) {
  spring_mesh.convertToSprings(mesh, mass);
  spring_mesh.calculateSpringConstants(k, d);
}