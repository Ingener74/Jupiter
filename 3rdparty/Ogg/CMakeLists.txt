cmake_minimum_required(VERSION 2.8.11)

set(EXT_OGG ext_Ogg)

unset(PATCH_FILE)

if(MINGW OR MSYS)
    ExternalProject_Add(
        ${EXT_OGG}
        URL                 http://downloads.xiph.org/releases/ogg/libogg-1.3.2.tar.gz
        CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/Ogg/${EXT_OGG}-prefix/src/${EXT_OGG}/configure --prefix=${3RDPARTY_INSTALL}
        BUILD_COMMAND       make
        INSTALL_COMMAND     make install
    )
elseif(EMSCRIPTEN)
elseif(ANDROID)
else()
    ExternalProject_Add(
        ${EXT_OGG}
        URL                 http://downloads.xiph.org/releases/ogg/libogg-1.3.2.tar.gz
        CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/Ogg/${EXT_OGG}-prefix/src/${EXT_OGG}/configure --prefix=${3RDPARTY_INSTALL}
        BUILD_COMMAND       make
        INSTALL_COMMAND     make install
    )
endif()
