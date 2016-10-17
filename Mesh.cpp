//
// Created by awbrenn on 10/16/16.
//

#include <sstream>
#include <fstream>
#include "Mesh.h"
#include "Vector.h"

bool Mesh::loadObj(char *obj_filename) {
  bool succeeded = true;
  std::string line;
  std::ifstream obj_file("box.obj");
  std::vector<Vector3d> temp_vertices;
  std::vector<Vector3d> temp_uvs;
  std::vector<Vector3d> temp_normals;


  if (obj_file.is_open()) {
    // read through the file
    while (getline(obj_file, line)) {
      std::stringstream line_stream(line);
      std::string type;
      line_stream >> type;

      if (type.compare("v") == 0) {
        std::cout << "vertex found" << std::endl;
      }
    }
  }
  else {
    succeeded = false;
  }

  return succeeded;
}
