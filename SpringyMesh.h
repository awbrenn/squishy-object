//
// Created by awbrenn on 10/20/16.
//

#ifndef SQUISHYMESH_SPRINGYMESH_H
#define SQUISHYMESH_SPRINGYMESH_H

#include <math.h>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
#include "Strut.h"
#include "Face.h"
#include "VertexParticle.h"
#include "Mesh.h"


class SpringyMesh {
  private:
    unsigned int addStrut(unsigned int v1, unsigned int v2, unsigned int face_index); // returns index of added strut
    double calculateAverageStrutLength();

  public:
    std::vector<Strut> struts;
    std::vector<Face> faces;
    std::vector<VertexParticle> vparticles;

    // calculates the spring constants based on time constant parameters
    void calculateSpringConstants(double spring_constant, double damper_constant);

    // converts a mesh to springs
    void convertToSprings(Mesh mesh, double mass);

    // checks if a strut already exists
    bool strutDoesNotExist(unsigned int v1, unsigned int v2, unsigned int *index);

    // converts a spring mesh back to a render mesh
    void convertToRenderMesh(Mesh* mesh);

    // get the vertices of a given face
    std::vector<VertexParticle> getVerticesOfFace(unsigned int face_index);

    // get the vertex indices of a given face
    std::vector<unsigned int> getVertexIndicesOfFace(unsigned int face_index);

    // calculate the angle between two faces

    // get the vertices not shared by two faces
    std::vector<unsigned int> getUnsharedVertices(unsigned int face1_index, unsigned int face2_index);

    // calculate the normal of a face
    Vector3d calculateFaceNormal(unsigned int face_index);

    // calculate angle between faces
    double calculateAngleBetweenFaces(unsigned int strut_index);
};


#endif //SQUISHYMESH_SPRINGYMESH_H
