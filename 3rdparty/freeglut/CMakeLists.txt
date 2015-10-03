cmake_minimum_required(VERSION 2.8.11)

set(EXT_FREEGLUT ext_freeglut)

if(MINGW OR MSYS)
    ExternalProject_Add(
        ${EXT_FREEGLUT}
        URL                 http://downloads.sourceforge.net/project/freeglut/freeglut/3.0.0/freeglut-3.0.0.tar.gz
        CMAKE_ARGS          -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                            -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                            -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DFREEGLUT_BUILD_DEMOS=OFF 
                            -DFREEGLUT_REPLACE_GLUT=OFF
    )
elseif(EMSCRIPTEN)
    # Emscripten already contain glut
elseif(ANDROID)
    # Using EGL
elseif(APPLE)
else()
    ExternalProject_Add(
        ${EXT_FREEGLUT}
        URL                 http://downloads.sourceforge.net/project/freeglut/freeglut/3.0.0/freeglut-3.0.0.tar.gz
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DFREEGLUT_BUILD_DEMOS=OFF 
                            -DFREEGLUT_REPLACE_GLUT=OFF
    )
endif()
