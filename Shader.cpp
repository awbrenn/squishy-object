//
// Created by awbrenn on 10/18/16.
//
#define GL_GLEXT_PROTOTYPES 1

#include "Shader.h"

Shader::Shader(char *vert, char *frag) {
  program = loadShaders(vert, frag);
}

char* Shader::readShaderProgram(char *filename) {
  std::string contents;
  std::ifstream in(filename, std::ios::in | std::ios::binary);

  std::cout << filename << std::endl;

  if (in) {
    in.seekg(0, std::ios::end);
    contents.reserve((unsigned long) in.tellg());
    in.seekg(0, std::ios::beg);
    contents.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();
  }
  else {
    std::cerr << "Could not read shader" << std::endl;
    exit(EXIT_FAILURE);
  }

  return (char *) contents.c_str();
}

void Shader::setUniformParameter(unsigned int p, char* varName, unsigned int value) {
  int location = glGetUniformLocation(p, varName);
  glUniform1i(location, value);
}

unsigned int Shader::loadShaders(char* vert, char* frag) {
  char *vs, *fs;
  GLuint v, f, p;

  v = glCreateShader(GL_VERTEX_SHADER);
  f = glCreateShader(GL_FRAGMENT_SHADER);

  vs = readShaderProgram(vert);
  fs = readShaderProgram(frag);

  glShaderSource(v,1,(const char **)&vs,NULL);
  glShaderSource(f,1,(const char **)&fs,NULL);

  glCompileShader(v);
  glCompileShader(f);

  p = glCreateProgram();
  glAttachShader(p,f);
  glAttachShader(p,v);
  glLinkProgram(p);

  glUseProgram(p);
  setUniformParameter(p, (char *) "myDiffuse", 0);
  setUniformParameter(p, (char *) "myNormal", 1);
  setUniformParameter(p, (char *) "mySpecular", 2);
  setUniformParameter(p, (char *) "myShadow", 3);

  return p;
}