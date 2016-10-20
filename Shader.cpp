//
// Created by awbrenn on 10/18/16.
//
#define GL_GLEXT_PROTOTYPES 1

#include "Shader.h"

Shader::Shader(char *frag, char *vert) {
  program = loadShaders(frag, vert);
}

char* Shader::readShaderProgram(char *filename) {
  FILE *fp;
  char *content = NULL;
  int fd, count;
  fd = open(filename,O_RDONLY);
  count = lseek(fd,0,SEEK_END);
  close(fd);
  content = (char *)calloc(1,(count+1));
  fp = fopen(filename,"r");
  count = fread(content,sizeof(char),count,fp);
  content[count] = '\0';
  fclose(fp);
  return content;
}

void Shader::setUniformParameter(unsigned int p, char* varName, unsigned int value) {
  int location = glGetUniformLocation(p, varName);
  glUniform1i(location, value);
}

unsigned int Shader::loadShaders(char* frag, char* vert) {
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
  if (p == 0) {std::cerr << "Failed to create program" << std::endl; exit(EXIT_FAILURE);}
  glAttachShader(p,f);
  glAttachShader(p,v);
  glLinkProgram(p);

  // print out any erros with shaders
  GLsizei lengthf;
  GLchar infologf[10000];
  glGetShaderInfoLog(f, 10000, &lengthf, infologf);
  std::cout << "Frag shader compilation: " << lengthf << "\n" << infologf << std::endl;

  GLsizei lengthv;
  GLchar infologv[10000];
  glGetShaderInfoLog(v, 10000, &lengthv, infologv);
  std::cout << "Vert shader compilation: " << lengthv << "\n" << infologv << std::endl;

  // print out errors with linking
  GLint link_status;
  glGetProgramiv(p, GL_LINK_STATUS, &link_status);
  if (link_status == GL_FALSE) {
      GLsizei length;
      GLchar infolog[10000];
      glGetProgramInfoLog(p, 10000, &length, infolog);
      std::cout << "Failed to link program: " << length << "\n" << infolog << std::endl;
      exit(EXIT_FAILURE);
  }

//  glUseProgram(p);
//  setUniformParameter(p, (char *) "myDiffuse", 0);
//  setUniformParameter(p, (char *) "myNormal", 1);
//  setUniformParameter(p, (char *) "mySpecular", 2);
//  setUniformParameter(p, (char *) "myShadow", 3);

  return p;
}