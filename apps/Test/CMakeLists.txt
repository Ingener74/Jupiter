cmake_minimum_required(VERSION 2.8)

include_directories(.)

add_executable(Test-1 main.cpp v1/v1.cpp Shaders.cpp Tools.cpp)
target_link_libraries(Test-1 ${GL_LIBRARIES} lodepng)

add_executable(Test-1-8 main.cpp button/button.cpp Shaders.cpp Tools.cpp)
target_link_libraries(Test-1-8 ${GL_LIBRARIES} lodepng)

add_executable(Test-2 
    main.cpp 
    Shaders.cpp 
    Tools.cpp
    v2/v2.cpp 
    v2/Attribute.cpp
    v2/Uniform.cpp
    v2/Program.cpp
    )
target_link_libraries(Test-2 ${GL_LIBRARIES} lodepng)
