cmake_minimum_required(VERSION 2.8.11)

if(MINGW)
else()
    add_definitions(-fPIC)
endif()

add_library(lodepng lodepng.cpp)
