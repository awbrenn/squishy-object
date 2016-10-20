//
// Created by awbrenn on 10/16/16.
//

#include "Mesh.h"

bool Mesh::loadObj(std::string obj_filename) {
  bool succeeded = true;
  std::string line;
  std::ifstream obj_file(obj_filename);
  std::vector<GLuv> temp_uvs;
  std::vector<GLnormal> temp_normals;


  if (obj_file.is_open()) {
    // read through the file
    while (getline(obj_file, line)) {
      std::stringstream line_stream(line);
      std::string type;
      line_stream >> type;

      if (type.compare("v") == 0) {
        GLvertex vertex;
        line_stream >> vertex.x >> vertex.y >> vertex.z;
        vertices.push_back(vertex);
//        std::cout << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
      }
      else if (type.compare("vt") == 0) {
        GLuv uv;
        line_stream >> uv.x >> uv.y;
        temp_uvs.push_back(uv);
//        std::cout << uv.x << " " << uv.y << " " << std::endl;
      }
      else if (type.compare("vn") == 0) {
        GLnormal normal;
        line_stream >> normal.x >> normal.y >> normal.z;
        temp_normals.push_back(normal);
//        std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
      }
      else if (type.compare("f") == 0) {
        unsigned int vertex_index[3], uv_index[3], normal_index[3];
        char delimiter;
        line_stream >> vertex_index[0] >> delimiter >> uv_index[0] >> delimiter >> normal_index[0]
                    >> vertex_index[1] >> delimiter >> uv_index[1] >> delimiter >> normal_index[1]
                    >> vertex_index[2] >> delimiter >> uv_index[2] >> delimiter >> normal_index[2];


//        std::cout << vertex_index[0] << " " << uv_index[0] << " " << normal_index[0] << std::endl
//                  << vertex_index[1] << " " << uv_index[1] << " " << normal_index[1] << std::endl
//                  << vertex_index[2] << " " << uv_index[2] << " " << normal_index[2] << std::endl << std::endl;

        GLface face = {
                vertices[vertex_index[0]-1],
                vertices[vertex_index[1]-1],
                vertices[vertex_index[2]-1],
                temp_normals[normal_index[0]-1],
                temp_normals[normal_index[1]-1],
                temp_normals[normal_index[2]-1],
                temp_uvs[uv_index[0]-1],
                temp_uvs[uv_index[1]-1],
        };

        GLfaces.push_back(face);

        FaceIndices f_indices {
                vertex_index[0] - 1,
                vertex_index[1] - 1,
                vertex_index[2] - 1
        };

        face_indices.push_back(f_indices);
      }
    }
  }
  else {
    succeeded = false;
  }

  return succeeded;
}
