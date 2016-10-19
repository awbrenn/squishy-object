//
// Created by awbrenn on 10/16/16.
//

#ifndef SQUISHYMESH_MESH_H
#define SQUISHYMESH_MESH_H
#include <vector>
#include <string>
#include "Vector.h"
#include <sstream>
#include <fstream>

#include <GL/gl.h>

typedef struct GLvertex {
  GLfloat x, y, z;
} GLvertex;

typedef struct GLnormal {
  GLfloat x, y, z;
} GLnormal;

typedef struct GLuv {
  GLfloat x, y;
} GLuv;

typedef struct GLface {
  GLvertex v[3]; // vertex
  GLnormal vn[3]; // vertex normal
  GLuv uv[3]; // uv coordinate
} GLface;

class Mesh {
  private:
    std::vector<unsigned int> vertex_indices;
    std::vector<unsigned int> uv_indices;
    std::vector<unsigned int> normal_indices;

  public:
    unsigned int number_of_faces = 0;
    std::vector<GLface> GLfaces;

    bool loadObj(std::string obj_filename);
};


#endif //SQUISHYMESH_MESH_H
