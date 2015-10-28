cmake_minimum_required(VERSION 2.8.11)

if(MINGW)
else()
    add_definitions(-fPIC)
endif()

add_library(lodepng lodepng/lodepng.cpp)

include(ExternalProject)

if(NOT FIND_PACKAGE_BOOST AND WITH_GAME_PLAYER)
    add_subdirectory(boost)
endif()

if(NOT FIND_PACKAGE_BOX2D)
    add_subdirectory(Box2D)
endif()

if(NOT FIND_PACKAGE_FREEGLUT)
    add_subdirectory(freeglut)
endif()

if(NOT FIND_PACKAGE_GLFW)
    add_subdirectory(GLFW)
endif()

if(NOT FIND_PACKAGE_GLEW)
    add_subdirectory(GLEW)
endif()

if(NOT FIND_PACKAGE_GLM)
    add_subdirectory(GLM)
endif()

if(NOT FIND_PACKAGE_LUA)
    add_subdirectory(Lua)
endif()

if(NOT FIND_PACKAGE_LIBPNG)
    add_subdirectory(libpng)
endif()

if(NOT FIND_PACKAGE_OPENAL)
    add_subdirectory(OpenAL)
endif()

if(NOT FIND_PACKAGE_FREETYPE)
    add_subdirectory(FreeType)
endif()

if(NOT FIND_PACKAGE_OGG)
    add_subdirectory(Ogg)
endif()

if(NOT FIND_PACKAGE_VORBIS)
    add_subdirectory(Vorbis)
endif()

add_subdirectory(mpg123)

add_subdirectory(gmock)