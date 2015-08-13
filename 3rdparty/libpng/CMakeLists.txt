cmake_minimum_required(VERSION 2.8.11)

set(EXT_PNG ext_libpng)

if(NOT FIND_PACKAGE_LIBPNG)
    
    if(MINGW)
    elseif(MSYS)
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
    else()
    endif()
        
    if(MINGW)
#        set(libpng_build_method "")
#        if(CMAKE_TOOLCHAIN_FILE)
#            message(STATUS "libpng CMAKE_TOOLCHAIN_FILE method")
#            set(libpng_build_method -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
#        elseif(CMAKE_GENERATOR STREQUAL "MSYS Makefiles")
#            message(STATUS "libpng MSYS Makefiles method")
#            set(libpng_build_method -G "MSYS Makefiles")
#        elseif(CMAKE_GENERATOR STREQUAL "MinGW Makefiles")
#            message(STATUS "libpng MinGW Makefiles method")
#            set(libpng_build_method -G "MinGW Makefiles")
#        else()
#            message(FATAL_ERROR "libpng unknown method")
#        endif()
#        ExternalProject_Add(
#            ${EXT_PNG}
#            URL                 http://downloads.sourceforge.net/project/libpng/libpng16/1.6.18/libpng-1.6.18.tar.xz
#            CMAKE_ARGS          ${libpng_build_method}
#                                -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
#                                -DPNG_SHARED=ON
#                                -DPNG_STATIC=ON
#                                -DPNG_TESTS=OFF
#                                -DPNG_DEBUG=OFF
#                                -DPNG_FRAMEWORK=OFF
#                                -DZLIB_INCLUDE_DIR=${3RDPARTY_INSTALL}/include
#                                -DZLIB_LIBRARY=${3RDPARTY_INSTALL}/lib/libzlib.dll.a
#        )
        ExternalProject_Add(
            ${EXT_PNG}
            URL                 http://downloads.sourceforge.net/project/libpng/libpng16/1.6.18/libpng-1.6.18.tar.xz
            CONFIGURE_COMMAND   ${CMAKE_BINARY_DIR}/3rdparty/libpng/${EXT_PNG}-prefix/src/${EXT_PNG}/configure --prefix=${3RDPARTY_INSTALL}
            BUILD_COMMAND       make
            INSTALL_COMMAND     make install
        )
    else()
        add_definitions(-fPIC)
    endif()

endif()

