//
// Created by awbrenn on 10/20/16.
//

#ifndef SQUISHYMESH_SPRINGYMESH_H
#define SQUISHYMESH_SPRINGYMESH_H

#include <vector>
#include "Strut.h"
#include "Face.h"
#include "VertexParticle.h"
#include "Mesh.h"

class SpringyMesh {
  private:
    unsigned int addStrut(unsigned int v1, unsigned int v2, unsigned int face_index); // returns index of added strut

  public:
    std::vector<Strut> struts;
    std::vector<Face> faces;
    std::vector<VertexParticle> vparticles;

    void convertToSprings(Mesh mesh);
    bool strutDoesNotExist(unsigned int v1, unsigned int v2, unsigned int *index);
};


#endif //SQUISHYMESH_SPRINGYMESH_H
