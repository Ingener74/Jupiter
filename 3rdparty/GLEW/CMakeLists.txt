cmake_minimum_required(VERSION 2.8.11)

set(EXT_GLEW ext_GLEW)

if(MINGW)
    ExternalProject_Add(
        ${EXT_GLEW}
        URL                 http://downloads.sourceforge.net/project/glew/glew/1.12.0/glew-1.12.0.tgz
        PATCH_COMMAND       patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/mingw.patch
        CMAKE_ARGS          -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
    )
else()
    add_definitions(-fPIC)
endif()
