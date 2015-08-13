cmake_minimum_required(VERSION 2.8.11)

set(EXT_LUA ext_Lua)

if(MINGW)
    set(Lua_build_method "")
    
    if(CMAKE_TOOLCHAIN_FILE)
        message(STATUS "Box2D CMAKE_TOOLCHAIN_FILE method")
        set(Lua_build_method -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
    elseif(CMAKE_GENERATOR STREQUAL "MSYS Makefiles")
        message(STATUS "Box2D MSYS Makefiles method")
        set(Lua_build_method -G "MSYS Makefiles")
    else()
        message(FATAL_ERROR "Box2D unknown method")
    endif()
    
    ExternalProject_Add(
        ${EXT_LUA}
        URL                 https://github.com/erincatto/Box2D/archive/v2.3.1.zip
        PATCH_COMMAND       patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/box2d.patch
        CONFIGURE_COMMAND   cmake ${CMAKE_BINARY_DIR}/3rdparty/Box2D/${EXT_LUA}-prefix/src/${EXT_LUA}/Box2D 
                                    ${Lua_build_method}
                                    -DBOX2D_INSTALL=ON
                                    -DBOX2D_BUILD_EXAMPLES=OFF
                                    -DBOX2D_BUILD_SHARED=ON
                                    -DBOX2D_BUILD_STATIC=ON
                                    -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
    )
else()
    add_definitions(-fPIC)
endif()
