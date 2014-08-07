cmake_minimum_required(VERSION 2.8.11)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

# find Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core    REQUIRED)
find_package(Qt5OpenGL  REQUIRED)

# find boost
find_package(Boost 1.53.0 REQUIRED system thread filesystem)

# find png
find_package(PNG REQUIRED)

# find glm
find_package(GLM REQUIRED)

# find GLUT
find_package(GLUT REQUIRED)

# find GLEW
find_package(GLEW REQUIRED)

# find Lua
find_package(Lua REQUIRED)

include_directories(
    ${Qt5Widgets_INCLUDES}
    ${Qt5Core_INCLUDES}
    ${Qt5OpenGL_INCLUDES}
    
    ${Boost_INCLUDE_DIRS}
    
    ${PNG_INCLUDE_DIRS}
    
    ${GLM_INCLUDE_DIRS}
    
    ${GLUT_INCLUDE_DIR}

    ${GLEW_INCLUDE_DIRS}
    
    ${LUA_INCLUDE_DIR}
    
    modules/Jupiter/include
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

add_definitions(
    -std=c++11
    ${Qt5Widgets_DEFINITIONS}
    ${Qt5Core_DEFINITIONS}
    ${Qt5OpenGL_DEFINITIONS}
)

add_subdirectory(apps)

add_subdirectory(modules)

add_subdirectory(samples)