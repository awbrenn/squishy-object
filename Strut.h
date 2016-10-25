//
// Created by awbrenn on 10/18/16.
//

#ifndef SQUISHYMESH_STRUT_H
#define SQUISHYMESH_STRUT_H

#define UNASSIGNED -1

class Strut {
  public:
    double k; // spring constant
    double d; // damper constant
    double torsional_k; // torsional spring constant
    double torsional_d; //
    double l0; // original length of strut
    unsigned int v1; // index of first vertex
    unsigned int v2; // index of second vertex
    int f1; // index of first face
    int f2; // index of second face
    double angle0;

    Strut(double K, double D, double L0, unsigned int V1, unsigned int V2, int F1, int F2);
};


#endif //SQUISHYMESH_STRUT_H
