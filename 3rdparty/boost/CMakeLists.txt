cmake_minimum_required(VERSION 2.8.11)

set(EXT_BOOST ext_boost)

if(NOT FIND_PACKAGE_BOOST)
    if(MINGW AND MSYS)
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
    else()
        ExternalProject_Add(
            ${EXT_BOOST}
            URL                 http://downloads.sourceforge.net/project/boost/boost/1.59.0/boost_1_59_0.tar.gz
            BINARY_DIR          ${CMAKE_BINARY_DIR}/3rdparty/boost/${EXT_BOOST}-prefix/src/${EXT_BOOST}
            CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/boost/${EXT_BOOST}-prefix/src/${EXT_BOOST}/bootstrap.sh
            # BUILD_COMMAND       ${CMAKE_BINARY_DIR}/3rdparty/boost/${EXT_BOOST}-prefix/src/${EXT_BOOST}/b2 variant=release link=static threading=multi runtime-link=static
            BUILD_COMMAND       ${CMAKE_BINARY_DIR}/3rdparty/boost/${EXT_BOOST}-prefix/src/${EXT_BOOST}/b2 variant=release link=static threading=multi
            INSTALL_COMMAND     ./b2 install --prefix=${3RDPARTY_INSTALL}
        )
    endif()
endif()
