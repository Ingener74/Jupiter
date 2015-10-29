cmake_minimum_required(VERSION 2.8.11)

set_source_files_properties(Jupiter.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(Jupiter.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")

set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin)

# Ещё ошибоньки
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\Sprite.h(31) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\Sprite.h(42) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\Transform.h(37) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\Transform.h(38) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\Camera.h(54) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\Camera.h(56) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\Body.h(37) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\Body.h(39) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\Body.h(41) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\VisualBody.h(26) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\VisualBody.h(28) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\VisualBody.h(30) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.

#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\NodeVisitor.h(63) : Warning 314: 'end' is a Lua keyword, renaming to 'c_end'
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\RenderVisitor.h(55) : Warning 314: 'end' is a Lua keyword, renaming to 'c_end'
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\PrintVisitor.h(28) : Warning 314: 'end' is a Lua keyword, renaming to 'c_end'
#C:\Users\Pavel\workspace\Jupiter\modules\Jupiter\include\Jupiter\Physics.h(33) : Warning 314: 'end' is a Lua keyword, renaming to 'c_end'

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