cmake_minimum_required(VERSION 2.8.11)

#add_subdirectory(3rdparty)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

# find boost
find_package(Boost 1.53.0 REQUIRED system thread filesystem program_options)

# find png
find_package(PNG REQUIRED)

# find glm
find_package(GLM REQUIRED)

option(USE_FREEGLUT "Use freeglut as window system" ON)
option(USE_GLFW "Use GLFW as window system" OFF)

if(USE_FREEGLUT AND USE_GLFW)
    message(FATAL_ERROR "Use freeglut OR glfw")
endif()

if(NOT USE_FREEGLUT AND NOT USE_GLFW)
    message(FATAL_ERROR "Use freeglut OR glfw")
endif()

# find GLUT
if(USE_FREEGLUT)
    find_package(GLUT REQUIRED)
    add_definitions(-DUSE_FREEGLUT)
endif()

# find GLFW
if(USE_GLFW)
    add_definitions(-DUSE_GLFW)
#    find_package(PkgConfig REQUIRED)
#    pkg_search_module(GLFW REQUIRED glfw3)

    find_package(GLFW REQUIRED)
    message(STATUS "glfw includes = ${GLFW_INCLUDE_DIR}")
    message(STATUS "glfw libs     = ${GLFW_LIBRARIES}")
endif()

# find GLEW
find_package(GLEW REQUIRED)

# find Box2D
find_package(Box2D REQUIRED)

# find Lua
find_package(Lua REQUIRED)

# find GTest and GMock
add_subdirectory(3rdparty/gmock-1.7.0)
enable_testing()

include_directories(
    ${Boost_INCLUDE_DIRS}
    
    ${PNG_INCLUDE_DIRS}
    
    ${GLM_INCLUDE_DIRS}
    
    ${GLUT_INCLUDE_DIR}
    
    ${GLFW_INCLUDE_DIR}
    
    ${GLEW_INCLUDE_DIRS}
    
    ${BOX2D_INCLUDE_DIR}
    
    ${LUA_INCLUDE_DIR}
    
    ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}
    ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR}
    
    3rdparty/Selene/include
    
    modules/Jupiter/include
    modules/Ganymede/include
)

# GL libraries
set(GL_LIBRARIES
    GL
    ${GLEW_LIBRARIES}
)
if(USE_FREEGLUT)
    set(GL_LIBRARIES ${GL_LIBRARIES} ${GLUT_LIBRARIES})
elseif(USE_GLFW)
    set(GL_LIBRARIES ${GL_LIBRARIES} ${GLFW_LIBRARIES})
endif()

add_definitions(-std=c++11)

add_subdirectory(apps)

add_subdirectory(modules)

add_subdirectory(samples)

option(WITH_WRAPPERS "Wrapper" OFF)

if(WITH_WRAPPERS)
    add_subdirectory(wrappers)
endif()

