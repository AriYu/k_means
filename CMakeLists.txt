cmake_minimum_required(VERSION 2.8)
project( k_means )

#########################################################
# FIND Open CV
#########################################################
find_package( OpenCV REQUIRED )
#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
ADD_DEFINITIONS(
  -g
  -O0
  -Wall
  -std=c++11
  )
add_executable( 
  test test.cpp k_means.cpp 
  )
target_link_libraries( test ${OpenCV_LIBS} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
