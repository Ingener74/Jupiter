cmake_minimum_required(VERSION 2.8)

add_executable(Test 
    Test.cpp
    Shaders.cpp
)

target_link_libraries(Test ${GL_LIBRARIES} ${GLEW_LIBRARIES})
