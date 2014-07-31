cmake_minimum_required(VERSION 2.8.11)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

# find Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core    REQUIRED)

# find png
find_package(PNG REQUIRED)

# find glm
find_package(GLM REQUIRED)

include_directories(
    ${Qt5Widgets_INCLUDES}
    ${Qt5Core_INCLUDES}
    
    ${PNG_INCLUDE_DIRS}
    
    ${GLM_INCLUDE_DIRS}

    modules/Jupiter/include
)

add_definitions(
    ${Qt5Widgets_DEFINITIONS}
    ${Qt5Core_DEFINITIONS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

add_definitions(-std=c++11)

add_subdirectory(apps)

add_subdirectory(modules)