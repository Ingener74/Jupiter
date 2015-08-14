cmake_minimum_required(VERSION 2.8.11)

set(EXT_GLEW ext_GLEW)

if(MINGW OR MSYS)
    set(GLEW_build_method "")
    
    if(CMAKE_TOOLCHAIN_FILE)
        message(STATUS "GLEW CMAKE_TOOLCHAIN_FILE method")
        set(GLEW_build_method -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
    elseif(CMAKE_GENERATOR STREQUAL "MSYS Makefiles")
        message(STATUS "GLEW MSYS Makefiles method")
        set(GLEW_build_method -G "MSYS Makefiles")
    else()
        message(FATAL_ERROR "GLEW unknown method")
    endif()
    
    ExternalProject_Add(
        ${EXT_GLEW}
        URL                 http://downloads.sourceforge.net/project/glew/glew/1.12.0/glew-1.12.0.tgz
        PATCH_COMMAND       patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/mingw.patch
        CMAKE_ARGS          ${GLEW_build_method} -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
    )
elseif(EMSCRIPTEN)
elseif(ANDROID)
else()
    ExternalProject_Add(
        ${EXT_GLEW}
        URL                 http://downloads.sourceforge.net/project/glew/glew/1.12.0/glew-1.12.0.tgz
        PATCH_COMMAND       patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/mingw2.patch
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
    )
endif()
