//
// Created by awbrenn on 10/16/16.
//

#ifndef SQUISHYMESH_MESH_H
#define SQUISHYMESH_MESH_H
#include <vector>
#include <string>

class Mesh {
  public:
    std::vector<unsigned int> vertex_indices;
    std::vector<unsigned int> uv_indices;
    std::vector<unsigned int> normal_indices;

    bool loadObj(char * obj_filename);
};


#endif //SQUISHYMESH_MESH_H
