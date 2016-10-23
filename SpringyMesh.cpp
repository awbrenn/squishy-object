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

void SpringyMesh::convertToRenderMesh(Mesh *mesh) {
  // TODO: average the vertex normals for vertices with multiple faces
  for (auto f = faces.begin(); f != faces.end(); ++f) {
    unsigned int face_index = f - faces.begin();
    std::vector<VertexParticle> face_vertices;

    // get face vertices
    face_vertices = getVerticesOfFace(f);

    // apply new vertex positions
    mesh->GLfaces[face_index].v[0].x = (GLfloat) (face_vertices[0].pos.x);
    mesh->GLfaces[face_index].v[0].y = (GLfloat) (face_vertices[0].pos.y);
    mesh->GLfaces[face_index].v[0].z = (GLfloat) (face_vertices[0].pos.z);

    mesh->GLfaces[face_index].v[1].x = (GLfloat) (face_vertices[1].pos.x);
    mesh->GLfaces[face_index].v[1].y = (GLfloat) (face_vertices[1].pos.y);
    mesh->GLfaces[face_index].v[1].z = (GLfloat) (face_vertices[1].pos.z);

    mesh->GLfaces[face_index].v[2].x = (GLfloat) (face_vertices[2].pos.x);
    mesh->GLfaces[face_index].v[2].y = (GLfloat) (face_vertices[2].pos.y);
    mesh->GLfaces[face_index].v[2].z = (GLfloat) (face_vertices[2].pos.z);

    // cross two of the struts to get the normal of the face
    VertexParticle *s1v1 = &vparticles[struts[f->strut_indices[0]].v1]; // strut 1 vertex 1
    VertexParticle *s1v2 = &vparticles[struts[f->strut_indices[0]].v2]; // strut 1 vertex 2
    VertexParticle *s2v1 = &vparticles[struts[f->strut_indices[1]].v1]; // strut 2 vertex 1
    VertexParticle *s2v2 = &vparticles[struts[f->strut_indices[1]].v2]; // strut 2 vertex 1

    // cross the two struts
    Vector3d strut_1 = (s1v2->pos - s1v1->pos).normalize();
    Vector3d strut_2 = (s2v2->pos - s2v1->pos).normalize();

    Vector3d normal = (strut_1 % strut_2).normalize();

    // apply the new face normal to the vertices
    mesh->GLfaces[face_index].vn[0].x = (GLfloat) (normal.x);
    mesh->GLfaces[face_index].vn[0].y = (GLfloat) (normal.y);
    mesh->GLfaces[face_index].vn[0].z = (GLfloat) (normal.z);

    mesh->GLfaces[face_index].vn[1].x = (GLfloat) (normal.x);
    mesh->GLfaces[face_index].vn[1].y = (GLfloat) (normal.y);
    mesh->GLfaces[face_index].vn[1].z = (GLfloat) (normal.z);

    mesh->GLfaces[face_index].vn[2].x = (GLfloat) (normal.x);
    mesh->GLfaces[face_index].vn[2].y = (GLfloat) (normal.y);
    mesh->GLfaces[face_index].vn[2].z = (GLfloat) (normal.z);
  }
}

std::vector<VertexParticle> SpringyMesh::getVerticesOfFace(std::vector<Face>::iterator face) {
  std::vector<VertexParticle> face_vertices;

  // grab the three vertices in the face
  face_vertices.push_back(vparticles[struts[face->strut_indices[0]].v1]);
  face_vertices.push_back(vparticles[struts[face->strut_indices[0]].v2]);
  face_vertices.push_back(vparticles[struts[face->strut_indices[1]].v2]);

  return face_vertices;
}
