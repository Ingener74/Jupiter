cmake_minimum_required(VERSION 2.8.11)

# http://downloads.sourceforge.net/project/mpg123/mpg123/1.22.4/mpg123-1.22.4.tar.bz2

set(EXT_MPG123 ext_mpg123)

unset(PATCH_FILE)

if(MINGW OR MSYS)
    ExternalProject_Add(
        ${EXT_MPG123}
        URL                 http://downloads.sourceforge.net/project/mpg123/mpg123/1.22.4/mpg123-1.22.4.tar.bz2
        CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/mpg123/${EXT_MPG123}-prefix/src/${EXT_MPG123}/configure --prefix=${3RDPARTY_INSTALL}
        BUILD_COMMAND       make
        INSTALL_COMMAND     make install
    )
elseif(EMSCRIPTEN)
elseif(ANDROID)
else()
    ExternalProject_Add(
        ${EXT_MPG123}
        URL                 http://downloads.sourceforge.net/project/mpg123/mpg123/1.22.4/mpg123-1.22.4.tar.bz2
        CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/mpg123/${EXT_MPG123}-prefix/src/${EXT_MPG123}/configure --prefix=${3RDPARTY_INSTALL}
        BUILD_COMMAND       make
        INSTALL_COMMAND     make install
    )
endif()
