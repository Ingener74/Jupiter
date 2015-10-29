cmake_minimum_required(VERSION 2.8.11)

set_source_files_properties(Jupiter.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(Jupiter.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")

set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin)

set(SHARED_LIBS
    Jupiter 
    ${OPENGL_LIB}
    ${GLEW_LIB}
    ${BOX2D_LIB}
)

if (NOT ANDROID AND NOT EMSCRIPTEN)

    # Lua
    if(WITH_LUA_WRAPPER)
        SWIG_ADD_MODULE(JupiterLua lua Jupiter.i)
        SWIG_LINK_LIBRARIES(JupiterLua ${SHARED_LIBS} ${LUA_LIB})
    endif()
    
    # Python
    if(WITH_PYTHON_WRAPPER)
        SWIG_ADD_MODULE(JupiterPython python Jupiter.i)
        SWIG_LINK_LIBRARIES(JupiterPython ${SHARED_LIBS} ${PYTHON_LIBRARIES})
    endif()

endif()

if (NOT EMSCRIPTEN) 

    if(ANDROID)
        # Java
        if(WITH_JAVA_WRAPPER)
            SWIG_ADD_MODULE(JupiterJava java Jupiter.i)
            set_target_properties(JupiterJava PROPERTIES NO_SONAME OFF)
            SWIG_LINK_LIBRARIES(JupiterJava ${SHARED_LIBS} android)
        endif()
    else()
        # Java
        if(WITH_JAVA_WRAPPER)
            SWIG_ADD_MODULE(JupiterJava java Jupiter.i)
            set_target_properties(JupiterJava PROPERTIES NO_SONAME OFF)
            SWIG_LINK_LIBRARIES(JupiterJava ${SHARED_LIBS})
        endif()
    endif()

endif()