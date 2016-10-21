//
// Created by awbrenn on 10/20/16.
//

#include "SpringyMesh.h"

bool SpringyMesh::strutDoesNotExist(unsigned int v1, unsigned int v2, unsigned int *index) {
  bool does_not_exist = true;

  // if there is a strut that contains both vertices, we return false
  for (auto s = struts.begin(); s != struts.end(); ++s) {
    if ((s->v1 == v1 and s->v2 == v2) or (s->v2 == v1 and s->v1 == v2)) {
      does_not_exist = false;
      *index = s - struts.begin();
    }
  }

  return does_not_exist;
}

void SpringyMesh::convertToSprings(Mesh mesh, double mass) {
  double even_mass = mass / ((double) (mesh.vertices.size()));

  for (auto v = mesh.vertices.begin(); v != mesh.vertices.end(); ++v) {
    vparticles.push_back(VertexParticle(Vector3d(v->x, v->y, v->z), Vector3d(0.0, 0.0, 0.0), even_mass));
  }

  // add struts and faces
  for (auto f = mesh.face_indices.begin(); f != mesh.face_indices.end(); ++f) {
    unsigned int face_index = f - mesh.face_indices.begin();
    unsigned  int strut_indices[3];
    strut_indices[0] = addStrut(f->v0, f->v1, face_index);
    strut_indices[1] = addStrut(f->v1, f->v2, face_index);
    strut_indices[2] = addStrut(f->v2, f->v0, face_index);
    faces.push_back(Face(strut_indices[0], strut_indices[1], strut_indices[2]));
  }
}

// TODO: calculate actual K and D for strut
unsigned int SpringyMesh::addStrut(unsigned int v1, unsigned int v2, unsigned face_index) {
  double l0; // initial length of strut
  unsigned int strut_index;

  if (strutDoesNotExist(v1, v2, &strut_index)) {
    l0 = (vparticles[v1].pos - vparticles[v2].pos).norm();
    struts.push_back(Strut(1.0, 1.0, l0, v1, v2, face_index, 0));
    strut_index = (unsigned int) (struts.size() - 1); // index is the last strut in the list
    struts[strut_index].f2 = UNASSIGNED; // set the face to unassigned
  }
  else {
    struts[strut_index].f2 = face_index; // if the strut exists already set the second face
  }

  return strut_index;
}

double SpringyMesh::calculateAverageStrutLength() {
  double average_strut_length = 0;

  for (auto s = struts.begin(); s != struts.end(); ++s) {
    average_strut_length += (vparticles[s->v1].pos - vparticles[s->v2].pos).norm();
  }

  return average_strut_length / ((double) (struts.size()));
}

void SpringyMesh::calculateSpringConstants(double spring_constant, double damper_constant) {
  double average_strut_length = calculateAverageStrutLength();

  for (auto s = struts.begin(); s != struts.end(); ++s) {
    s->k = (s->l0 / average_strut_length) * spring_constant;
    s->d = (s->l0 / average_strut_length) * damper_constant;
  }
}