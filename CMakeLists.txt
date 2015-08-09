cmake_minimum_required(VERSION 2.8.11)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")


option(USE_FREEGLUT               "Use freeglut as window system"   ON)
option(USE_GLFW                   "Use GLFW as window system"       OFF)
                                  
option(WITH_WRAPPERS              "Wrapper"                         ON)
option(WITH_LUA_WRAPPER           "Lua wrapper"                     ON)
option(WITH_PYTHON_WRAPPER        "Python wrapper"                  ON)
                                  
option(WITH_GANIMEDE              "Build Ganimede"                  OFF)
option(WITH_GAME_PLAYER           "Build with c++ game player"      ON)

option(WITH_GLFW_PYTHON_WRAPPER   "Build GLFW Python Wrapper"       ON)
option(WITH_GLFW_LUA_WRAPPER      "Build GLFW Lua Wrapper"          ON)
                                                                    
option(WITH_GLEW_PYTHON_WRAPPER   "Build GLEW Python Wrapper"       ON)
option(WITH_GLEW_LUA_WRAPPER      "Build GLEW Lua Wrapper"          ON)
                                                                    
option(WITH_GL_PYTHON_WRAPPER     "Build GL Python Wrapper"         ON)
option(WITH_GL_LUA_WRAPPER        "Build GL Lua Wrapper"            ON)

option(WITH_GLM_PYTHON_WRAPPER    "Build glm Python Wrapper"        ON)
option(WITH_GLM_LUA_WRAPPER       "Build glm Lua Wrapper"           ON)

option(WITH_BOX2D_PYTHON_WRAPPER  "Build Box2D Python Wrapper"      ON)
option(WITH_BOX2D_LUA_WRAPPER     "Build Box2D Lua Wrapper"         ON)

option(WITH_TEST_PROGRAMS         "Build test programs Test1, Test2" ON)

if(USE_FREEGLUT AND USE_GLFW)
    message(FATAL_ERROR "Use freeglut OR glfw")
endif()
if(NOT USE_FREEGLUT AND NOT USE_GLFW)
    message(FATAL_ERROR "Use freeglut OR glfw")
endif()


if(WITH_GAME_PLAYER)

    # find boost
    set(Boost_USE_STATIC_LIBS    ON)
    set(Boost_USE_MULTITHREADED  ON)
    if(MINGW)
        set(Boost_COMPILER -mgw48)
    else()
        set(Boost_COMPILER -gcc)
    endif()
    
    find_package(Boost 1.53.0 REQUIRED system filesystem program_options)

endif()

# find png
find_package(PNG REQUIRED)

find_package(FreeImage)

# find glm
find_package(GLM REQUIRED)

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
if(WITH_GANIMEDE)
endif()
find_package(Lua)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(3rdparty)

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
    
    3rdparty/json/src
    3rdparty/lodepng
    
    modules/Jupiter/include
    modules/Ganymede/include
)
include_directories(${INCLUDE_DIRS})

# find Lua
if(WITH_GANIMEDE)
endif()

find_package(Lua)
if(LUA_FOUND)
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${LUA_INCLUDE_DIR})
endif()

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
if(MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
else()
#    add_definitions(-fPIC)
endif()

add_subdirectory(apps)

add_subdirectory(modules)

add_subdirectory(samples)

if(WITH_WRAPPERS)
    add_subdirectory(wrappers)
endif()

