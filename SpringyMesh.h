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
};


#endif //SQUISHYMESH_SPRINGYMESH_H
