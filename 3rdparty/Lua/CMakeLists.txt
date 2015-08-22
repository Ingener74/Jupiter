cmake_minimum_required(VERSION 2.8.11)

set(EXT_LUA ext_Lua)

unset(PATCH_FILE)
unset(ADDITIONAL_FLAGS)

if(MINGW OR MSYS)
    if(CMAKE_TOOLCHAIN_FILE)
        set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
    elseif(CMAKE_GENERATOR STREQUAL "MSYS Makefiles")
        set(ADDITIONAL_FLAGS -G "MSYS Makefiles")
    else()
        message(FATAL_ERROR "Lua unknown method")
    endif()

elseif(EMSCRIPTEN)
    set(PATCH_FILE        ${CMAKE_CURRENT_LIST_DIR}/emscripten.patch)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                         -DBUILD_SHARED_LIBS=OFF
                         -DCMAKE_C_FLAGS="-Wno-warn-absolute-paths"
                         -DCMAKE_CXX_FLAGS="-Wno-warn-absolute-paths")
elseif(ANDROID)
    set(PATCH_FILE        ${CMAKE_CURRENT_LIST_DIR}/android.patch)
    set(ADDITIONAL_FLAGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                         -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
    )
else()
endif()

if(PATCH_FILE)
    ExternalProject_Add(
        ${EXT_LUA}
        URL                 https://github.com/LuaDist/lua/archive/5.2.3.zip
        PATCH_COMMAND       patch -p1 < ${PATCH_FILE}
        CMAKE_ARGS          ${ADDITIONAL_FLAGS} -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
    )
else()
    ExternalProject_Add(
        ${EXT_LUA}
        URL                 https://github.com/LuaDist/lua/archive/5.2.3.zip
        CMAKE_ARGS          ${ADDITIONAL_FLAGS} -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
    )
endif()