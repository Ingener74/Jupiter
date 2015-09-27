cmake_minimum_required(VERSION 2.8.11)

set(EXT_VORBIS ext_Vorbis)

unset(PATCH_FILE)

if(MINGW OR MSYS)
    ExternalProject_Add(
        ${EXT_VORBIS}
        URL                 http://downloads.xiph.org/releases/vorbis/libvorbis-1.3.5.tar.gz
        CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/Vorbis/${EXT_VORBIS}-prefix/src/${EXT_VORBIS}/configure --prefix=${3RDPARTY_INSTALL} --enable-examples
        BUILD_COMMAND       make
        INSTALL_COMMAND     make install
    )
elseif(EMSCRIPTEN)
elseif(ANDROID)
else()
    ExternalProject_Add(
        ${EXT_VORBIS}
        URL                 http://downloads.xiph.org/releases/vorbis/libvorbis-1.3.5.tar.gz
        CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/Vorbis/${EXT_VORBIS}-prefix/src/${EXT_VORBIS}/configure --prefix=${3RDPARTY_INSTALL} --enable-examples
        BUILD_COMMAND       make
        INSTALL_COMMAND     make install
    )
endif()
