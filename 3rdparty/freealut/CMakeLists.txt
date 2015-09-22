cmake_minimum_required(VERSION 2.8.11)

set(EXT_FREEALUT ext_freealut)

unset(ADDITIONAL_FLAGS)
unset(PATCH_FILE)

if(MINGW OR MSYS)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} 
                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                         -DCMAKE_
                         -DOPENAL_LIB=${3RDPARTY_INSTALL}/lib/libOpenAL32.dll.a
     )

elseif(EMSCRIPTEN)
# contain OpenAL itself

elseif(ANDROID)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                         -DOPENAL_LIB=${3RDPARTY_INSTALL}/lib/libopenal.so
    )

else()
endif()

if(NOT EMSCRIPTEN)
    ExternalProject_Add(
        ${EXT_FREEALUT}
        URL                 https://github.com/vancegroup/freealut/archive/freealut_1_1_0.zip
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL} 
                            ${ADDITIONAL_FLAGS}
                            
    )
endif()