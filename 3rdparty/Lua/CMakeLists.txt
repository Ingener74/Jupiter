cmake_minimum_required(VERSION 2.8.11)

set(EXT_LUA ext_Lua)

if(MINGW)
    set(Lua_build_method "")
    
    if(CMAKE_TOOLCHAIN_FILE)
        message(STATUS "Lua CMAKE_TOOLCHAIN_FILE method")
        set(Lua_build_method -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
    elseif(CMAKE_GENERATOR STREQUAL "MSYS Makefiles")
        message(STATUS "Lua MSYS Makefiles method")
        set(Lua_build_method -G "MSYS Makefiles")
    else()
        message(FATAL_ERROR "Lua unknown method")
    endif()
    
    ExternalProject_Add(
        ${EXT_LUA}
        URL                 https://github.com/LuaDist/lua/archive/5.2.3.zip
        CMAKE_ARGS          ${Lua_build_method} -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
    )
else()
    add_definitions(-fPIC)
endif()
