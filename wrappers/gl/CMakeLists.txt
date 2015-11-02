cmake_minimum_required(VERSION 2.8.11)

if (NOT ANDROID AND NOT EMSCRIPTEN)

    set_source_files_properties(gl.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(gl.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")
    
    if(WITH_GL_LUA_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/GL/Lua)
    
        SWIG_ADD_MODULE(glLua lua gl.i)
        SWIG_LINK_LIBRARIES(glLua ${OPENGL_LIBRARIES} ${GLEW_LIB} ${LUA_LIB})
    endif()
    
    if(WITH_GL_PYTHON_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/GL/Python)
    
        SWIG_ADD_MODULE(glPython python gl.i)
        SWIG_LINK_LIBRARIES(glPython ${OPENGL_LIBRARIES} ${GLEW_LIB} ${PYTHON_LIBRARIES})
    endif()

    if(WITH_GL_CSHARP_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/GL/CSharp)
    
        SWIG_ADD_MODULE(glCSharp csharp gl.i)
        SWIG_LINK_LIBRARIES(glCSharp ${OPENGL_LIBRARIES} ${GLEW_LIB})
    endif()

endif()
