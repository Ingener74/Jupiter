cmake_minimum_required(VERSION 2.8.11)

set(EXT_BOOST ext_boost)

if(MINGW OR MSYS)

elseif(EMSCRIPTEN)

elseif(ANDROID)

else()
    ExternalProject_Add(
        ${EXT_BOOST}
        URL                 http://downloads.sourceforge.net/project/boost/boost/1.59.0/boost_1_59_0.tar.gz
        BINARY_DIR          ${CMAKE_BINARY_DIR}/3rdparty/boost/${EXT_BOOST}-prefix/src/${EXT_BOOST}
        CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/boost/${EXT_BOOST}-prefix/src/${EXT_BOOST}/bootstrap.sh
        BUILD_COMMAND       ${CMAKE_BINARY_DIR}/3rdparty/boost/${EXT_BOOST}-prefix/src/${EXT_BOOST}/b2 install variant=release link=static threading=multi --with-system --with-filesystem --with-program_options --prefix=${3RDPARTY_INSTALL} -d0
        INSTALL_COMMAND     ""
    )

endif()
