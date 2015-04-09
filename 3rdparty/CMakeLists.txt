cmake_minimum_required(VERSION 2.8.11)

add_definitions(-fPIC)
add_library(lodepng lodepng/lodepng.cpp)

if(WITH_TESTS)
    # find GTest and GMock
    add_subdirectory(gmock-1.7.0)
    enable_testing()
endif()
