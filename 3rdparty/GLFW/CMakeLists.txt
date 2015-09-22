cmake_minimum_required(VERSION 2.8.11)

set(EXT_GLFW ext_GLFW)

if(MINGW OR MSYS)
    ExternalProject_Add(
        ${EXT_GLFW}
        URL                 https://github.com/glfw/glfw/archive/3.1.1.zip
        PATCH_COMMAND       patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/mingw.patch
        CMAKE_ARGS          -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                            -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                            -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DBUILD_SHARED_LIBS=ON
    )

elseif(EMSCRIPTEN)
    # Emscripten already contain some
elseif(ANDROID)
    # Using EGL
else()
    ExternalProject_Add(
        ${EXT_GLFW}
        URL                 https://github.com/glfw/glfw/archive/3.1.1.zip
        CMAKE_ARGS          -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                            -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                            -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                            -DBUILD_SHARED_LIBS=ON
    )

endif()

