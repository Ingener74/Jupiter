cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME Callisto)
project(${PROJECT_NAME})

#include_directories(src/asteroids)

set(SOURCES
    src/GamePlayer.cpp
)

if(OPENGL_WINDOW_SYSTEM STREQUAL "FreeGLUT")
    set(SOURCES ${SOURCES} src/GlutMain.cpp)
elseif(OPENGL_WINDOW_SYSTEM STREQUAL "GLFW")
    set(SOURCES ${SOURCES} src/GLFWMain.cpp)
else()
    message(FATAL_ERROR "Invalid OpenGL window system")
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
    ${OPENGL_LIBRARIES} 
    ${GLEW_LIB}
    ${GL_WINDOW}
    ${BOOST_LIB}
    ${PNG_LIB}

    Jupiter
)

target_link_libraries(${PROJECT_NAME} lodepng ${LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION Jupiter/bin)
