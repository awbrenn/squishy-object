//
// Created by awbrenn on 10/18/16.
//

#ifndef SQUISHYMESH_FACE_H
#define SQUISHYMESH_FACE_H

class Face {
  public:
    unsigned int strut_indices[3]; // indices of struts

    Face(unsigned int strut_index1, unsigned int strut_index2, unsigned int strut_index3);
};

#endif //SQUISHYMESH_FACE_H
