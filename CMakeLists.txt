cmake_minimum_required(VERSION 2.8.11)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

option(FIND_PACKAGE_BOOST         "" ON)
option(FIND_PACKAGE_BOX2D         "" OFF)
option(FIND_PACKAGE_FREEGLUT      "" OFF)
option(FIND_PACKAGE_GLFW          "" OFF)
option(FIND_PACKAGE_GLEW          "" OFF)
option(FIND_PACKAGE_GLM           "" OFF)
option(FIND_PACKAGE_LUA           "" OFF)
option(FIND_PACKAGE_LIBPNG        "" OFF)

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

set(OPENGL_WINDOW_SYSTEM "FreeGLUT" CACHE STRING "Select a OpenGL window system")
set_property(CACHE OPENGL_WINDOW_SYSTEM PROPERTY STRINGS "FreeGLUT" "GLFW")

if(MINGW AND MSYS)
    message(STATUS "MinGW or MSYS build")
elseif(EMSCRIPTEN)
    message(STATUS "Emscripten build")
elseif(ANDROID)
    message(STATUS "Android build")
else()
    message(STATUS "Linux build")
endif()

# find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

set(3RDPARTY_INSTALL ${CMAKE_BINARY_DIR}/install)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${3RDPARTY_INSTALL}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${3RDPARTY_INSTALL}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${3RDPARTY_INSTALL}/lib)

add_subdirectory(3rdparty)

include_directories(
    3rdparty/json/src
    3rdparty/lodepng
    
    modules/Jupiter/include
    modules/Ganymede/include
    
    ${3RDPARTY_INSTALL}/include
)

link_directories(${3RDPARTY_INSTALL}/lib)

# Libraries sets

# Lua
set(LUA_LIB)
if(FIND_PACKAGE_LUA)
    find_package(Lua)
    include_directories(${LUA_INCLUDE_DIR})
    set(LUA_LIB ${LUA_LIB} ${LUA_LIBRARIES})
else()
    set(LUA_LIB ${LUA_LIB} lua)
endif()

# GLEW
set(GLEW_LIB)
if(FIND_PACKAGE_GLEW)
    find_package(GLEW REQUIRED)
    set(GLEW_LIB ${GLEW_LIB} ${GLEW_LIBRARIES})
else()
    set(GLEW_LIB ${GLEW_LIB} glew32 glew32mx)
endif()

# FreeGLUT and GLFW
set(GL_WINDOW)
if(OPENGL_WINDOW_SYSTEM STREQUAL "FreeGLUT")
    if(FIND_PACKAGE_FREEGLUT)
        include_directories(${GLUT_INCLUDE_DIR})
        set(GL_WINDOW ${GL_WINDOW} ${GLUT_LIBRARIES})
    else()
        if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
            set(GL_WINDOW ${GL_WINDOW} glut)
        elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
            set(GL_WINDOW ${GL_WINDOW} freeglut)
        else()
            message(FATAL_ERROR "error")
        endif()
    endif()
elseif(OPENGL_WINDOW_SYSTEM STREQUAL "GLFW")
    if(FIND_PACKAGE_GLFW)
        include_directories(${GLFW_INCLUDE_DIR})
        set(GL_WINDOW ${GL_WINDOW} ${GLFW_LIBRARIES})
    else()
        message(FATAL_ERROR "OPENGL_WINDOW_SYSTEM -> FIND_PACKAGE_GLFW Not implemented")
    endif()
else()
    message(FATAL_ERROR "Invalid OpenGL window system")
endif()

# GLM
if(FIND_PACKAGE_GLM)
    # find glm
    find_package(GLM REQUIRED)
    include_directories(${GLM_INCLUDE_DIRS})
endif()

# Box2D
set(BOX2D_LIB)
if(FIND_PACKAGE_BOX2D)
    find_package(Box2D REQUIRED)
    include_directories(${BOX2D_INCLUDE_DIR})
    set(BOX2D_LIB ${BOX2D_LIB} ${BOX2D_LIBRARIES})
else()
    set(BOX2D_LIB ${BOX2D_LIB} Box2D)
endif()

# Boost
set(BOOST_LIB)
if(WITH_GAME_PLAYER)
    if(FIND_PACKAGE_BOOST)
    
        if(MINGW)
        elseif(EMSCRIPTEN)
        else()
            set(Boost_USE_STATIC_LIBS    ON)
            set(Boost_USE_MULTITHREADED  ON)
            if(MINGW)
                set(Boost_COMPILER -mgw48)
            else()
                set(Boost_COMPILER -gcc)
            endif()
            
            find_package(Boost 1.53.0 REQUIRED system filesystem program_options)
        endif()
    
        include_directories(${Boost_INCLUDE_DIRS})
        set(BOOST_LIB ${BOOST_LIB} ${Boost_LIBRARIES})
    else()
        message(FATAL_ERROR "Boost not from find_package not supported yet")
    endif()
endif()

# PNG
set(PNG_LIB)
if(FIND_PACKAGE_LIBPNG)
    find_package(PNG REQUIRED)
    include_directories(${PNG_INCLUDE_DIRS})
    set(PNG_LIB ${PNG_LIB} ${PNG_LIBRARIES})
else()
endif()

add_definitions(-std=c++11)
if(MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
    
#    include_directories(
#        ${CMAKE_BINARY_DIR}/3rdparty/GLEW/${EXT_GLEW}-prefix/src/${EXT_GLEW}/include
#    )
elseif(EMSCRIPTEN)
else()
#    add_definitions(-fPIC)
endif()

add_subdirectory(apps)

add_subdirectory(modules)

add_subdirectory(samples)

if(WITH_WRAPPERS)
    add_subdirectory(wrappers)
endif()

