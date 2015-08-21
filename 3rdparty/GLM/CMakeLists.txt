cmake_minimum_required(VERSION 2.8.11)

set(EXT_GLM ext_GLM)

unset(ADDITIONAL_FLAGS)

if(MINGW OR MSYS)
    if(CMAKE_TOOLCHAIN_FILE)
        set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
    elseif(CMAKE_GENERATOR STREQUAL "MSYS Makefiles")
        set(ADDITIONAL_FLAGS -G "MSYS Makefiles")
    else()
        message(FATAL_ERROR "GLM unknown method")
    endif()
    
elseif(EMSCRIPTEN)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
elseif(ANDROID)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
else()
endif()

ExternalProject_Add(
    ${EXT_GLM}
    URL                 https://github.com/g-truc/glm/archive/0.9.7.0.zip
    CMAKE_ARGS          ${ADDITIONAL_FLAGS} -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
)
