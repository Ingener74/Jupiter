cmake_minimum_required(VERSION 2.8.11)

include_directories(
    3rdparty/lua/src
)

add_subdirectory(3rdparty)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

# find boost
find_package(Boost 1.53.0 REQUIRED system thread filesystem program_options)

# find png
find_package(PNG REQUIRED)

# find glm
find_package(GLM REQUIRED)

# find GLUT
find_package(GLUT REQUIRED)

# find GLEW
find_package(GLEW REQUIRED)

# find Box2D
find_package(Box2D REQUIRED)

# find GTest and GMock
add_subdirectory(3rdparty/gmock-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(
    ${Boost_INCLUDE_DIRS}
    
    ${PNG_INCLUDE_DIRS}
    
    ${GLM_INCLUDE_DIRS}
    
    ${GLUT_INCLUDE_DIR}

    ${GLEW_INCLUDE_DIRS}
    
    ${BOX2D_INCLUDE_DIR}
    
    3rdparty/Selene/include
    
    modules/Jupiter/include
    modules/Ganymede/include
)

add_definitions(-std=c++11)

add_subdirectory(apps)

add_subdirectory(modules)

add_subdirectory(samples)

option(WITH_WRAPPERS "Wrapper" OFF)

if(WITH_WRAPPERS)
    add_subdirectory(wrappers)
endif()

