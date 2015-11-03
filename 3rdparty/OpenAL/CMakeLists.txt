cmake_minimum_required(VERSION 2.8.11)

set(EXT_OPENAL ext_OpenAL)

unset(ADDITIONAL_FLAGS)
unset(PATCH_FILE)

if(MINGW OR MSYS)
    set(ADDITIONAL_FLAGS    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} 
                            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                            -DCMAKE_GENERATOR=${CMAKE_GENERATOR})

elseif(EMSCRIPTEN)
# contain OpenAL itself

elseif(ANDROID)
    set(ADDITIONAL_FLAGS    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                            -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
    )

else()
    set(ADDITIONAL_FLAGS    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    )
endif()

if(NOT EMSCRIPTEN)
    ExternalProject_Add(
        ${EXT_OPENAL}
        URL                 http://kcat.strangesoft.net/openal-releases/openal-soft-1.16.0.tar.bz2
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL} 
                            ${ADDITIONAL_FLAGS}
    )
endif()
