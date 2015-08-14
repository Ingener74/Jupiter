cmake_minimum_required(VERSION 2.8.11)

set(EXT_PNG ext_libpng)

if(NOT FIND_PACKAGE_LIBPNG)
    if(MINGW OR MSYS)
        ExternalProject_Add(
            ${EXT_PNG}
            URL                 http://downloads.sourceforge.net/project/libpng/libpng16/1.6.18/libpng-1.6.18.tar.xz
            CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/libpng/${EXT_PNG}-prefix/src/${EXT_PNG}/configure --prefix=${3RDPARTY_INSTALL}
            BUILD_COMMAND       make
            INSTALL_COMMAND     make install
        )
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
    else()
        ExternalProject_Add(
            ${EXT_PNG}
            URL                 http://downloads.sourceforge.net/project/libpng/libpng16/1.6.18/libpng-1.6.18.tar.xz
            CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DPNG_SHARED=ON
                                -DPNG_STATIC=ON
                                -DPNG_TESTS=OFF
                                -DPNG_DEBUG=OFF
                                -DPNG_FRAMEWORK=OFF
        )
    endif()
endif()

