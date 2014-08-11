cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ../../3rdparty/lua/src/
)

add_executable(lua_parse_test 
    main.cpp
    ../../3rdparty/lua/src/lapi.c
    ../../3rdparty/lua/src/lauxlib.c
    ../../3rdparty/lua/src/lbaselib.c
    ../../3rdparty/lua/src/lbitlib.c
    ../../3rdparty/lua/src/lcode.c
    ../../3rdparty/lua/src/lcorolib.c
    ../../3rdparty/lua/src/lctype.c
    ../../3rdparty/lua/src/ldblib.c
    ../../3rdparty/lua/src/ldebug.c
    ../../3rdparty/lua/src/ldo.c
    ../../3rdparty/lua/src/ldump.c
    ../../3rdparty/lua/src/lfunc.c
    ../../3rdparty/lua/src/lgc.c
    ../../3rdparty/lua/src/linit.c
    ../../3rdparty/lua/src/liolib.c
    ../../3rdparty/lua/src/llex.c
    ../../3rdparty/lua/src/llimits.h
    ../../3rdparty/lua/src/lmathlib.c
    ../../3rdparty/lua/src/lmem.c
    ../../3rdparty/lua/src/loadlib.c
    ../../3rdparty/lua/src/lobject.c
    ../../3rdparty/lua/src/lopcodes.c
    ../../3rdparty/lua/src/loslib.c
    ../../3rdparty/lua/src/lparser.c
    ../../3rdparty/lua/src/lstate.c
    ../../3rdparty/lua/src/lstring.c
    ../../3rdparty/lua/src/lstrlib.c
    ../../3rdparty/lua/src/ltable.c
    ../../3rdparty/lua/src/ltablib.c
    ../../3rdparty/lua/src/ltm.c
    ../../3rdparty/lua/src/lundump.c
    ../../3rdparty/lua/src/lvm.c
    ../../3rdparty/lua/src/lzio.c
)
target_link_libraries(lua_parse_test ${Boost_LIBRARIES} dl)