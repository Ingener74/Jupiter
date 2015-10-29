cmake_minimum_required(VERSION 2.8.11)

if (NOT ANDROID AND NOT EMSCRIPTEN)

    set_source_files_properties(Box2D.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(Box2D.i PROPERTIES SWIG_FLAGS "")
    
    if(WITH_BOX2D_LUA_WRAPPER)
        SWIG_ADD_MODULE(Box2DLua lua Box2D.i)
        SWIG_LINK_LIBRARIES(Box2DLua ${BOX2D_LIB} ${LUA_LIB})
    endif()
    
    if(WITH_BOX2D_PYTHON_WRAPPER)
        SWIG_ADD_MODULE(Box2DPython python Box2D.i)
        SWIG_LINK_LIBRARIES(Box2DPython ${BOX2D_LIB} ${PYTHON_LIBRARIES})
    endif()

endif()
