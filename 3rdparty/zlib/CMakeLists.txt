cmake_minimum_required(VERSION 2.8.11)

if(MINGW)
    # ExternalProject_Add(
    #     ext_Box2D
    #     GIT_REPOSITORY  https://github.com/erincatto/Box2D.git
    #     GIT_TAG         v2.3.1
    #     CMAKE_ARGS      -G "MSYS Makefiles"
    #     )
    
    message(STATUS "!!!!!! make build for zlib")
else()
    add_definitions(-fPIC)
endif()

