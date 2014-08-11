cmake_minimum_required(VERSION 2.8.11)

add_executable(lua_parse_test main.cpp)
target_link_libraries(lua_parse_test ${Boost_LIBRARIES})