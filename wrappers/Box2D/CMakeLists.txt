cmake_minimum_required(VERSION 2.8.11)

if (NOT ANDROID AND NOT EMSCRIPTEN)

    set_source_files_properties(Box2D.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(Box2D.i PROPERTIES SWIG_FLAGS "")
    
    if(WITH_BOX2D_LUA_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/Box2D/Lua)
        
        SWIG_ADD_MODULE(Box2DLua lua Box2D.i)
        SWIG_LINK_LIBRARIES(Box2DLua ${BOX2D_LIB} ${LUA_LIB})
    endif()
    
    if(WITH_BOX2D_PYTHON_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/Box2D/Python)
        
        SWIG_ADD_MODULE(Box2DPython python Box2D.i)
        SWIG_LINK_LIBRARIES(Box2DPython ${BOX2D_LIB} ${PYTHON_LIBRARIES})
    endif()
    
    if(WITH_BOX2D_JAVA_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/Box2D/Java)
        
        SWIG_ADD_MODULE(Box2DJava java Box2D.i)
        SWIG_LINK_LIBRARIES(Box2DJava ${BOX2D_LIB})
    endif()

    if(WITH_BOX2D_CSHARP_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/Box2D/CSharp)
        
        SWIG_ADD_MODULE(Box2DCSharp csharp Box2D.i)
        SWIG_LINK_LIBRARIES(Box2DCSharp ${BOX2D_LIB})
    endif()

endif()
