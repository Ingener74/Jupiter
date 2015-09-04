cmake_minimum_required(VERSION 2.8.11)

set(EXT_OPENAL ext_OpenAL)

unset(ADDITIONAL_FLAGS)
unset(PATCH_FILE)

# http://kcat.strangesoft.net/openal-releases/openal-soft-1.16.0.tar.bz2

if(MINGW OR MSYS)
    #set(PATCH_FILE       ${CMAKE_CURRENT_LIST_DIR}/box2d.patch)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} 
                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR})

elseif(EMSCRIPTEN)
# contain OpenAL itself
elseif(ANDROID)
    #set(PATCH_FILE       ${CMAKE_CURRENT_LIST_DIR}/box2d.android.patch)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
    )

else()
    #set(PATCH_FILE       ${CMAKE_CURRENT_LIST_DIR}/box2d.patch)

endif()

if(NOT EMSCRIPTEN)
    ExternalProject_Add(
        ${EXT_OPENAL}
        URL                 http://kcat.strangesoft.net/openal-releases/openal-soft-1.16.0.tar.bz2
        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL} 
                            ${ADDITIONAL_FLAGS}
    )
endif()