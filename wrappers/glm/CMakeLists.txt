cmake_minimum_required(VERSION 2.8.11)

if (NOT ANDROID AND NOT EMSCRIPTEN)

    set_source_files_properties(glm.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(glm.i PROPERTIES SWIG_FLAGS "")
    
    #if(WITH_GL_LUA_WRAPPER)
    #    SWIG_ADD_MODULE(glLua lua gl.i)
    #    SWIG_LINK_LIBRARIES(glLua ${OPENGL_LIBRARIES} ${GLEW_LIB} ${LUA_LIB})
    #endif()
    
    if(WITH_GLM_PYTHON_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/glm/Python)
        SWIG_ADD_MODULE(glmPython python glm.i)
        SWIG_LINK_LIBRARIES(glmPython ${OPENGL_LIBRARIES} ${GLEW_LIB} ${PYTHON_LIBRARIES})
    endif()

endif()