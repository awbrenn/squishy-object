cmake_minimum_required(VERSION 3.3)

project(SquishyMesh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
add_compile_options(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

include_directories("/usr/include")
find_library(OIIO "OpenImageIO" "/usr/lib")
find_library(GLUT "glut")
find_library(GL "GL")
find_library(GLU "GLU")

set(SOURCE_FILES main.cpp Utility.cpp Camera.cpp Matrix.cpp Vector.cpp Mesh.cpp Mesh.h Object.cpp Object.h Strut.cpp Strut.h Face.cpp Face.h VertexParticle.cpp VertexParticle.h Shader.cpp Shader.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${GLUT} ${GL} ${GLU} ${OIIO} )
