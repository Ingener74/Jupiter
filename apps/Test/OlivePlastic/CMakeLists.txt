cmake_minimum_required(VERSION 2.8)

add_executable(OlivePlastic OlivePlastic.cpp)
target_link_libraries(OlivePlastic ${OPENAL_LIB} ${OGG_LIB} ${VORBIS_LIB})
