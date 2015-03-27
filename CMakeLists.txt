cmake_minimum_required(VERSION 2.8.11)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")


option(USE_FREEGLUT          "Use freeglut as window system"   ON)
option(USE_GLFW              "Use GLFW as window system"       OFF)

option(WITH_WRAPPERS         "Wrapper"                         OFF)
option(WITH_LUA_WRAPPER      "Lua wrapper"                     ON)
option(WITH_PYTHON_WRAPPER   "Python wrapper"                  ON)

option(WITH_GAME_PLAYER      "Build with c++ game player"      ON)

# find boost
find_package(Boost 1.53.0 REQUIRED system thread filesystem program_options)

# find png
find_package(PNG REQUIRED)

find_package(FreeImage)

# find glm
find_package(GLM REQUIRED)

if(USE_FREEGLUT AND USE_GLFW)
    message(FATAL_ERROR "Use freeglut OR glfw")
endif()

if(NOT USE_FREEGLUT AND NOT USE_GLFW)
    message(FATAL_ERROR "Use freeglut OR glfw")
endif()

# find GLUT
if(USE_FREEGLUT)
    add_definitions(-DUSE_FREEGLUT)
    find_package(GLUT REQUIRED)
endif()

# find GLFW
if(USE_GLFW)
    add_definitions(-DUSE_GLFW)
    find_package(GLFW REQUIRED)
endif()

# find OpenGL
find_package(OpenGL REQUIRED)

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
    
    ${OPENGL_INCLUDE_DIR}
    
    ${GLEW_INCLUDE_DIRS}
    
    ${BOX2D_INCLUDE_DIR}
    
    ${LUA_INCLUDE_DIR}
    
    ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}
    ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR}
    
    3rdparty/json/src
    
    modules/Jupiter/include
    modules/Ganymede/include
)

# GL libraries
set(GL_LIBRARIES
    ${OPENGL_LIBRARIES}
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

if(WITH_WRAPPERS)
    add_subdirectory(wrappers)
endif()

