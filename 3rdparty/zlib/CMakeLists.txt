cmake_minimum_required(VERSION 2.8.11)

set(EXT_ZLIB ext_zlib)

if(NOT FIND_PACKAGE_LIBPNG)
    
    if(MINGW)
    elseif(MSYS)
    elseif(EMSCRIPTEN)
    elseif(ANDROID)
    else()
    endif()
        
    if(MINGW)
        set(zlib_build_method "")
        
        if(CMAKE_TOOLCHAIN_FILE)
            message(STATUS "zlib CMAKE_TOOLCHAIN_FILE method")
            set(zlib_build_method -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
        elseif(CMAKE_GENERATOR STREQUAL "MSYS Makefiles")
            message(STATUS "zlib MSYS Makefiles method")
            set(zlib_build_method -G "MSYS Makefiles")
        else()
            message(FATAL_ERROR "zlib unknown method")
        endif()
        
        ExternalProject_Add(
            ${EXT_ZLIB}
            URL                 http://downloads.sourceforge.net/project/libpng/zlib/1.2.8/zlib-1.2.8.tar.gz
            CMAKE_ARGS          ${zlib_build_method}
                                -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
        )
    else()
        add_definitions(-fPIC)
    endif()

endif()

