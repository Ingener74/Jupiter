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
        set(libpng_build_method "")
        
        if(CMAKE_TOOLCHAIN_FILE)
            message(STATUS "libpng CMAKE_TOOLCHAIN_FILE method")
            set(libpng_build_method -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
        elseif(CMAKE_GENERATOR STREQUAL "MSYS Makefiles")
            message(STATUS "libpng MSYS Makefiles method")
            set(libpng_build_method -G "MSYS Makefiles")
        else()
            message(FATAL_ERROR "libpng unknown method")
        endif()
        
        ExternalProject_Add(
            ${EXT_PNG}
            URL                 http://downloads.sourceforge.net/project/libpng/libpng16/1.6.18/libpng-1.6.18.tar.xz
            CMAKE_ARGS          ${libpng_build_method}
                                -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                                -DPNG_SHARED=ON
                                -DPNG_STATIC=ON
                                -DPNG_TESTS=OFF
                                -DPNG_DEBUG=OFF
                                -DPNG_FRAMEWORK=OFF
                                -DZLIB_INCLUDE_DIR=${3RDPARTY_INSTALL}/include
                                -DZLIB_LIBRARY=${3RDPARTY_INSTALL}/lib/libzlib.dll.a
        )
    else()
        add_definitions(-fPIC)
    endif()

endif()

