cmake_minimum_required(VERSION 2.8.11)

set(EXT_GLM ext_GLM)

if(MINGW)
    set(GLM_build_method "")
    
    if(CMAKE_TOOLCHAIN_FILE)
        message(STATUS "GLM CMAKE_TOOLCHAIN_FILE method")
        set(GLM_build_method -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
    elseif(CMAKE_GENERATOR STREQUAL "MSYS Makefiles")
        message(STATUS "GLM MSYS Makefiles method")
        set(GLM_build_method -G "MSYS Makefiles")
    else()
        message(FATAL_ERROR "GLM unknown method")
    endif()
    
    ExternalProject_Add(
        ${EXT_GLM}
        URL                 https://github.com/g-truc/glm/archive/0.9.7.0.zip
        CMAKE_ARGS          ${GLM_build_method} -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
    )
else()
    add_definitions(-fPIC)
endif()
