//
// Created by awbrenn on 10/18/16.
//

#ifndef SQUISHYMESH_STRUT_H
#define SQUISHYMESH_STRUT_H

#define UNASSIGNED -1;

class Strut {
  public:
    double k; // spring constant
    double d; // damper constant
    double l0; // original length of strut
    unsigned int v1; // index of first vertex
    unsigned int v2; // index of second vertex
    unsigned int f1; // index of first face
    unsigned int f2; // index of second face

    Strut(double K, double D, double L0, unsigned int V1, unsigned int V2, unsigned int F1, unsigned int F2);
};


#endif //SQUISHYMESH_STRUT_H
