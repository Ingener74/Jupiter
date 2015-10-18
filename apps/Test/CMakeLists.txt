cmake_minimum_required(VERSION 2.8)

include_directories(.)

add_subdirectory(ViperFreaky)

if(OPENGL_WINDOW_SYSTEM STREQUAL "FreeGLUT")
    set(LIBS
        ${OPENGL_LIBRARIES} 
        ${GLEW_LIB} 
        ${GL_WINDOW}
    )

    add_executable(Test-1 
        main.cpp 
        v1/v1.cpp 
        Shaders.cpp 
        Tools.cpp
    )
    if(EMSCRIPTEN)
        target_link_libraries(Test-1 lodepng)
    else()
        target_link_libraries(Test-1 lodepng ${LIBS})
    endif()

    add_executable(Test-1-8 
        main.cpp 
        button/button.cpp 
        Shaders.cpp 
        Tools.cpp
    )
    target_link_libraries(Test-1-8 lodepng ${LIBS})

    add_executable(Test-2 
        main.cpp 
        Shaders.cpp 
        Tools.cpp
        v2/v2.cpp 
        v2/Attribute.cpp
        v2/Uniform.cpp
        v2/Program.cpp
    )
    target_link_libraries(Test-2 lodepng ${LIBS})

    add_executable(Test-4
        test-4.cpp
    )
    if(EMSCRIPTEN)
        target_link_libraries(Test-4 lodepng)
    else()
        target_link_libraries(Test-4 ${LIBS})
    endif()
    
    if(EMSCRIPTEN)
        add_executable(Test-5 test-5.cpp)
        target_link_libraries(Test-5 lodepng)
    endif()
    
    add_subdirectory(test-6)
    
    add_executable(OggVorbisOpenAL OggVorbisOpenAL.cpp)
    target_link_libraries(OggVorbisOpenAL ${OPENAL_LIB} ${OGG_LIB} ${VORBIS_LIB})
endif()
