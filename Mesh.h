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

#ifdef __APPLE__
  #include <OpenGL/gl.h>   // OpenGL itself.
#else
  #include <GL/gl.h>   // OpenGL itself.
#endif

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

typedef struct FaceIndices {
  unsigned int v0;
  unsigned int v1;
  unsigned int v2;
} FaceIndices;

class Mesh {
  public:
    std::vector<GLvertex> vertices;
    std::vector<FaceIndices> face_indices;
    unsigned int number_of_faces = 0;
    std::vector<GLface> GLfaces;

    bool loadObj(std::string obj_filename);
};


#endif //SQUISHYMESH_MESH_H
