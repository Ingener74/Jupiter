cmake_minimum_required(VERSION 2.8.11)

set(EXT_FREEGLUT ext_freeglut)

if(MINGW)
    set(freeglut_build_method "")
    
    if(CMAKE_TOOLCHAIN_FILE)
        message(STATUS "freeglut CMAKE_TOOLCHAIN_FILE method")
        set(freeglut_build_method -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
    elseif(CMAKE_GENERATOR STREQUAL "MSYS Makefiles")
        message(STATUS "freeglut MSYS Makefiles method")
        set(freeglut_build_method -G "MSYS Makefiles")
    else()
        message(FATAL_ERROR "freeglut unknown method")
    endif()
    
    ExternalProject_Add(
        ${EXT_FREEGLUT}
        URL                 http://downloads.sourceforge.net/project/freeglut/freeglut/3.0.0/freeglut-3.0.0.tar.gz
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
    )
else()
    add_definitions(-fPIC)
endif()
