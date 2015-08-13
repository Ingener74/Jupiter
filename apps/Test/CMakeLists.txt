cmake_minimum_required(VERSION 2.8)

include_directories(.)

if(USE_FREEGLUT)

    set(LIBS)
    if(MINGW)
        set(LIBS ${LIBS} 
            glew32 
            glew32mx
            )
        if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
            set(LIBS ${LIBS} glut)
        elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
            set(LIBS ${LIBS} freeglut)
        else()
            message(FATAL_ERROR "error")
        endif()
    else()
        set(LIBS ${LIBS}
            glut
        )
    endif()

    add_executable(Test-1 main.cpp v1/v1.cpp Shaders.cpp Tools.cpp)
    target_link_libraries(Test-1 ${GL_LIBRARIES} lodepng ${LIBS})

    add_executable(Test-1-8 main.cpp button/button.cpp Shaders.cpp Tools.cpp)
    target_link_libraries(Test-1-8 ${GL_LIBRARIES} lodepng ${LIBS})

    add_executable(Test-2 
        main.cpp 
        Shaders.cpp 
        Tools.cpp
        v2/v2.cpp 
        v2/Attribute.cpp
        v2/Uniform.cpp
        v2/Program.cpp
        )
    target_link_libraries(Test-2 ${GL_LIBRARIES} lodepng ${LIBS})

endif()
