cmake_minimum_required(VERSION 2.8.11)

if (NOT ANDROID AND NOT EMSCRIPTEN)

    set_source_files_properties(glfw.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(glfw.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")
    
    if(WITH_GLFW_LUA_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/GLFW/Lua)
        SWIG_ADD_MODULE(glfwLua lua glfw.i)
        SWIG_LINK_LIBRARIES(glfwLua ${GL_WINDOW} ${GLEW_LIB} ${LUA_LIB})
    endif()
    
    if(WITH_GLFW_PYTHON_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/GLFW/Python)
        SWIG_ADD_MODULE(glfwPython python glfw.i)
        SWIG_LINK_LIBRARIES(glfwPython ${GL_WINDOW} ${GLEW_LIB} ${PYTHON_LIBRARIES})
    endif()

    if(WITH_GLFW_JAVA_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/GLFW/Java)
        SWIG_ADD_MODULE(glfwJava java glfw.i)
        SWIG_LINK_LIBRARIES(glfwJava ${GL_WINDOW} ${GLEW_LIB})
    endif()

    if(WITH_GLFW_CSHARP_WRAPPER)
        set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/GLFW/CSharp)
        SWIG_ADD_MODULE(glfwCSharp csharp glfw.i)
        SWIG_LINK_LIBRARIES(glfwCSharp ${GL_WINDOW} ${GLEW_LIB})
    endif()

endif()
