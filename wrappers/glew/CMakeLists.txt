cmake_minimum_required(VERSION 2.8.11)

if (NOT ANDROID AND NOT EMSCRIPTEN)

    set_source_files_properties(glew.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(glew.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")
    
    if(WITH_GLEW_LUA_WRAPPER)
        SWIG_ADD_MODULE(glewLua lua glew.i)
        SWIG_LINK_LIBRARIES(glewLua ${OPENGL_LIBRARIES} ${GLEW_LIB} ${LUA_LIB})
    endif()
    
    if(WITH_GLEW_PYTHON_WRAPPER)
        SWIG_ADD_MODULE(glewPython python glew.i)
        SWIG_LINK_LIBRARIES(glewPython ${OPENGL_LIBRARIES} ${GLEW_LIB} ${PYTHON_LIBRARIES})
    endif()

endif()
