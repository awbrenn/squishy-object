//
// Created by awbrenn on 10/18/16.
//

#include "Face.h"

Face::Face(unsigned int strut_index1, unsigned int strut_index2, unsigned int strut_index3) {
  strut_indices[0] = strut_index1;
  strut_indices[1] = strut_index2;
  strut_indices[2] = strut_index3;
}
