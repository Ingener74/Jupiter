cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)
find_package(Qt5Core)

include_directories(
    ${Qt5Widgets_INCLUDES}
    ${Qt5Core_INCLUDES}
)

add_definitions(
    ${Qt5Widgets_DEFINITIONS}
    ${Qt5Core_DEFINITIONS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

add_definitions(-std=c++11)

add_subdirectory(apps)

