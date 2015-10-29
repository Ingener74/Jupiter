cmake_minimum_required(VERSION 2.8.11)

find_package(SWIG REQUIRED)
include(UseSWIG)

if(NOT ANDROID AND NOT EMSCRIPTEN)
    find_package(PythonLibs 2.7 REQUIRED)
endif()
#include_directories(
#    .
#)

find_package(Java REQUIRED)
if(NOT ANDROID AND NOT EMSCRIPTEN)
    find_package(JNI REQUIRED)
endif()
include(UseJava)

include_directories(
    ${PYTHON_INCLUDE_PATH} 
    ${JNI_INCLUDE_DIRS}
    ${JAVA_INCLUDE_PATH}
)

set(CMAKE_SWIG_FLAGS "-c++")
set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin)

add_subdirectory(Jupiter)

add_subdirectory(glfw)

add_subdirectory(glew)

add_subdirectory(gl)

add_subdirectory(glm)

add_subdirectory(Box2D)

