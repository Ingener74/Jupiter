cmake_minimum_required(VERSION 2.8.11)

set(EXT_PNG ext_libpng)

unset(PATCH_FILE)

set(PNG_URL "http://downloads.sourceforge.net/project/libpng/libpng16/older-releases/1.6.18/libpng-1.6.18.tar.xz")

if(MINGW OR MSYS)
    ExternalProject_Add(
        ${EXT_PNG}
        URL                 ${PNG_URL}
        CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/libpng/${EXT_PNG}-prefix/src/${EXT_PNG}/configure --prefix=${3RDPARTY_INSTALL}
        BUILD_COMMAND       make
        INSTALL_COMMAND     make install
    )
elseif(EMSCRIPTEN)
# 
# emmake make -S USE_LIBPNG=1 -s USE_ZLIB=1
# 
elseif(ANDROID)
    ExternalProject_Add(
        ${EXT_PNG}
        URL                 ${PNG_URL}
        PATCH_COMMAND       patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/android_win.patch
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DPNG_SHARED=OFF
                            -DPNG_STATIC=ON
                            -DPNG_TESTS=OFF
                            -DPNG_DEBUG=OFF
                            -DPNG_FRAMEWORK=OFF
                            -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                            -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
    )
else()
    ExternalProject_Add(
        ${EXT_PNG}
        URL                 ${PNG_URL}
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DPNG_SHARED=ON
                            -DPNG_STATIC=ON
                            -DPNG_TESTS=OFF
                            -DPNG_DEBUG=OFF
                            -DPNG_FRAMEWORK=OFF
    )
endif()
