cmake_minimum_required(VERSION 2.8.11)

if(MINGW)
else()
    add_definitions(-fPIC)
endif()

add_library(lodepng lodepng/lodepng.cpp)

if(WITH_TESTS)
    # find GTest and GMock
    add_subdirectory(gmock-1.7.0)
    enable_testing()
endif()
