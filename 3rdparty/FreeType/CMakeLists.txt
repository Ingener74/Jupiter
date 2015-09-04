cmake_minimum_required(VERSION 2.8.11)

set(EXT_FREETYPE ext_freetype)

unset(ADDITIONAL_FLAGS)

if(MINGW OR MSYS)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} 
                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR})

elseif(EMSCRIPTEN)
# contain freetype itself

elseif(ANDROID)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
    )

else()

endif()

if(NOT EMSCRIPTEN)
    ExternalProject_Add(
        ${EXT_FREETYPE}
        URL                 http://downloads.sourceforge.net/project/freetype/freetype2/2.6/freetype-2.6.tar.bz2
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL} 
                            ${ADDITIONAL_FLAGS}
    )
endif()