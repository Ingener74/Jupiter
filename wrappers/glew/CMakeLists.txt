cmake_minimum_required(VERSION 2.8.11)

if (NOT ANDROID AND NOT EMSCRIPTEN)

    set_source_files_properties(glew.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(glew.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")
    
    if(WITH_GLEW_LUA_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/GLEW/Lua)
    
        SWIG_ADD_MODULE(glewLua lua glew.i)
        SWIG_LINK_LIBRARIES(glewLua ${OPENGL_LIBRARIES} ${GLEW_LIB} ${LUA_LIB})
    endif()
    
    if(WITH_GLEW_PYTHON_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/GLEW/Python)
    
        SWIG_ADD_MODULE(glewPython python glew.i)
        SWIG_LINK_LIBRARIES(glewPython ${OPENGL_LIBRARIES} ${GLEW_LIB} ${PYTHON_LIBRARIES})
    endif()
    
    if(WITH_GLEW_CSHARP_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/GLEW/CSharp)
    
        SWIG_ADD_MODULE(glewCSharp csharp glew.i)
        SWIG_LINK_LIBRARIES(glewCSharp ${OPENGL_LIBRARIES} ${GLEW_LIB})
    endif()

    if(WITH_GLEW_JAVA_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/GLEW/Java)
    
        SWIG_ADD_MODULE(glewJava java glew.i)
        SWIG_LINK_LIBRARIES(glewJava ${OPENGL_LIBRARIES} ${GLEW_LIB})
    endif()

endif()
