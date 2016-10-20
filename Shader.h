//
// Created by awbrenn on 10/18/16.
//

#ifndef SQUISHYMESH_SHADER_H
#define SQUISHYMESH_SHADER_H

#ifdef __APPLE__
  #include <OpenGL/gl.h>   // OpenGL itself.
#else
  #include <GL/gl.h>   // OpenGL itself.
#endif

#include <stdio.h>
#include <fcntl.h>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <iostream>

class Shader {
  private:
    char* readShaderProgram(char* filename);
    void setUniformParameter(unsigned int p, char* varName, unsigned int value);
    unsigned int loadShaders(char* vert, char* frag);

  public:
    GLuint program;

    Shader(char* vert, char* frag);
};


#endif //SQUISHYMESH_SHADER_H
