//
// Created by awbrenn on 10/18/16.
//

#ifndef SQUISHYMESH_FACE_H
#define SQUISHYMESH_FACE_H

struct StrutIndexAngle {
  unsigned int index; // index of the strut
  double angle; // vertex angle of the strut
};

class Face {
  StrutIndexAngle s[3]; // indices and vertex angles of struts
};


#endif //SQUISHYMESH_FACE_H
