//
// Created by awbrenn on 10/18/16.
//
#define GL_GLEXT_PROTOTYPES 1

#include "Shader.h"

Shader::Shader(char *vert, char *frag) {
  program = loadShaders(vert, frag);
}

char* Shader::readShaderProgram(char *filename) {
  FILE *fp;
  char *content = NULL;
  int fd, count;
  fd = open(filename,O_RDONLY);
  count = (int)lseek(fd,0,SEEK_END);
  close(fd);
  content = (char *)calloc(1,(size_t)(count+1));
  fp = fopen(filename,"r");
  count = (int)fread(content,sizeof(char),(size_t)count,fp);
  content[count] = '\0';
  fclose(fp);
  return content;
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

  free(vs);
  free(fs);

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