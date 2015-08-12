cmake_minimum_required(VERSION 2.8.11)

set(EXT_BOOST ext_boost)

if(WITH_GAME_PLAYER)
    if(MINGW)
        set(boost_build_method "")
        
        ExternalProject_Add(
            ${EXT_BOOST}
            URL                 http://downloads.sourceforge.net/project/boost/boost/1.58.0/boost_1_58_0.tar.gz
            CONFIGURE_COMMAND   start ${CMAKE_BINARY_DIR}/3rdparty/boost/${EXT_BOOST}-prefix/src/${EXT_BOOST}/bootstrap.sh
        )
    else()
        add_definitions(-fPIC)
    endif()
endif()