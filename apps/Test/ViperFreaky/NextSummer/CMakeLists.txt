cmake_minimum_required(VERSION 3.0)

add_definitions(-fPIC)

set(SOURCES
    src/NextSummer.h
    src/NextSummer.cpp
)

add_library(NextSummer ${SOURCES})

find_package(SWIG)
include(${SWIG_USE_FILE})

find_package(PythonLibs 2.7 REQUIRED)
include_directories(
    ${PYTHON_INCLUDE_PATH} 
    src
)

set(CMAKE_SWIG_FLAGS "-c++")

set_source_files_properties(NextSummer.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(NextSummer.i PROPERTIES SWIG_FLAGS "-nodefaultctor")

set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin)

SWIG_ADD_MODULE(NextSummerPython python NextSummer.i)
SWIG_LINK_LIBRARIES(NextSummerPython NextSummer ${PYTHON_LIBRARIES})
