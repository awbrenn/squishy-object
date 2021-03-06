cmake_minimum_required(VERSION 2.8.4)

project(SquishyMesh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
add_compile_options(-std=c++11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories("/usr/local/include")
    find_library(OIIO "OpenImageIO" "/usr/local/lib")
    find_library(FOUNDATION "Foundation")
    find_library(GLUT "GLUT")
    find_library(OPENGL "OpenGL")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
    include_directories("/group/dpa/include")
    find_library(OIIO "OpenImageIO" "/group/dpa/lib")
    find_library(GLUT "glut")
    find_library(GL "GL")
    find_library(GLU "GLU")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

set(SOURCE_FILES main.cpp Utility.cpp Camera.cpp Matrix.cpp Vector.cpp Mesh.cpp Mesh.h Object.cpp Object.h Strut.cpp Strut.h Face.cpp Face.h VertexParticle.cpp VertexParticle.h Shader.cpp Shader.h SpringyMesh.cpp SpringyMesh.h SpringyObject.cpp SpringyObject.h Solver.cpp Solver.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(${PROJECT_NAME} ${OIIO} ${FOUNDATION} ${GLUT} ${OPENGL})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(${PROJECT_NAME} ${OIIO} ${GLUT} ${GL} ${GLU})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
