cmake_minimum_required(VERSION 2.8.11)

set(EXT_GLM ext_GLM)

unset(ADDITIONAL_FLAGS)

if(MINGW OR MSYS)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} 
                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR})
    
elseif(EMSCRIPTEN)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
    )
elseif(ANDROID)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
    )
else()
endif()

ExternalProject_Add(
    ${EXT_GLM}
    URL                 https://github.com/g-truc/glm/archive/0.9.7.0.zip
    CMAKE_ARGS          ${ADDITIONAL_FLAGS} -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
)
