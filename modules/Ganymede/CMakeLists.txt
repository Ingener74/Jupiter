cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME Ganymede)
project(${PROJECT_NAME})

set(SOURCES
    src/Boolean.cpp
    src/Function.cpp
    src/Nil.cpp
    src/Number.cpp
    src/State.cpp
    src/String.cpp
    src/Table.cpp
)
add_library(${PROJECT_NAME} STATIC ${SOURCES})

set(LIBS
    ${LUA_LIBRARIES}
)
target_link_libraries(${PROJECT_NAME} ${LIBS})