cmake_minimum_required(VERSION 2.8.11)

if (NOT ANDROID AND NOT EMSCRIPTEN)

    set_source_files_properties(glfw.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(glfw.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")
    
    if(WITH_GLFW_LUA_WRAPPER)
        SWIG_ADD_MODULE(glfwLua lua glfw.i)
        SWIG_LINK_LIBRARIES(glfwLua ${GL_WINDOW} ${GLEW_LIB} ${LUA_LIB})
    endif()
    
    if(WITH_GLFW_PYTHON_WRAPPER)
        SWIG_ADD_MODULE(glfwPython python glfw.i)
        SWIG_LINK_LIBRARIES(glfwPython ${GL_WINDOW} ${GLEW_LIB} ${PYTHON_LIBRARIES})
    endif()

endif()
