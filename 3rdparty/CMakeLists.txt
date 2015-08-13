cmake_minimum_required(VERSION 2.8.11)

if(MINGW)
else()
    add_definitions(-fPIC)
endif()

add_library(lodepng lodepng/lodepng.cpp)

include(ExternalProject)

add_subdirectory(Box2D)
add_subdirectory(GLEW)
add_subdirectory(GLM)
add_subdirectory(boost)
add_subdirectory(freeglut)
add_subdirectory(Lua)

add_subdirectory(zlib)
add_subdirectory(libpng)