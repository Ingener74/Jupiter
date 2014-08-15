cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME Ganymede)
project(${PROJECT_NAME})

set(SOURCES
    src/State.cpp
)
add_library(${PROJECT_NAME} STATIC ${SOURCES})

set(LIBS
    lua
)
target_link_libraries(${PROJECT_NAME} ${LIBS})