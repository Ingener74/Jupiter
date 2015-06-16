cmake_minimum_required(VERSION 2.8.11)

find_package(SWIG)
include(${SWIG_USE_FILE})

find_package(PythonLibs 2.7 REQUIRED)
include_directories(
    ${PYTHON_INCLUDE_PATH} 
    .
)

set(CMAKE_SWIG_FLAGS "-c++")

set_source_files_properties(Jupiter.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(Jupiter.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")

set(CMAKE_SWIG_OUTDIR ${CMAKE_BINARY_DIR}/bin)

set(SHARED_LIBS
    Jupiter 
    ${GL_LIBRARIES}
)

# Lua
if(WITH_LUA_WRAPPER)
    SWIG_ADD_MODULE(JupiterLua lua Jupiter.i)
    SWIG_LINK_LIBRARIES(JupiterLua ${SHARED_LIBS} ${LUA_LIBRARIES})
endif()

# Python
if(WITH_PYTHON_WRAPPER)
    SWIG_ADD_MODULE(JupiterPython python Jupiter.i)
    SWIG_LINK_LIBRARIES(JupiterPython ${SHARED_LIBS} ${PYTHON_LIBRARIES})
endif()

################################################################################################
# GLFW
################################################################################################
if(USE_GLFW)
    set_source_files_properties(glfw.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(glfw.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")
    
    if(WITH_GLFW_LUA_WRAPPER)
        SWIG_ADD_MODULE(glfwLua lua glfw.i)
        SWIG_LINK_LIBRARIES(glfwLua ${GL_LIBRARIES} ${LUA_LIBRARIES})
    endif()
    
    if(WITH_GLFW_PYTHON_WRAPPER)
        SWIG_ADD_MODULE(glfwPython python glfw.i)
        SWIG_LINK_LIBRARIES(glfwPython ${GL_LIBRARIES} ${PYTHON_LIBRARIES})
    endif()
endif()

################################################################################################
# GLEW
################################################################################################
set_source_files_properties(glew.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(glew.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")

if(WITH_GLEW_LUA_WRAPPER)
    SWIG_ADD_MODULE(glewLua lua glew.i)
    SWIG_LINK_LIBRARIES(glewLua ${GL_LIBRARIES} ${LUA_LIBRARIES})
endif()

if(WITH_GLEW_PYTHON_WRAPPER)
    SWIG_ADD_MODULE(glewPython python glew.i)
    SWIG_LINK_LIBRARIES(glewPython ${GL_LIBRARIES} ${PYTHON_LIBRARIES})
endif()

################################################################################################
# GL
################################################################################################
set_source_files_properties(gl.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(gl.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")

if(WITH_GL_LUA_WRAPPER)
    SWIG_ADD_MODULE(glLua lua gl.i)
    SWIG_LINK_LIBRARIES(glLua ${GL_LIBRARIES} ${LUA_LIBRARIES})
endif()

if(WITH_GL_PYTHON_WRAPPER)
    SWIG_ADD_MODULE(glPython python gl.i)
    SWIG_LINK_LIBRARIES(glPython ${GL_LIBRARIES} ${PYTHON_LIBRARIES})
endif()

################################################################################################
# glm
################################################################################################
set_source_files_properties(glm.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(glm.i PROPERTIES SWIG_FLAGS "")

#if(WITH_GL_LUA_WRAPPER)
#    SWIG_ADD_MODULE(glLua lua gl.i)
#    SWIG_LINK_LIBRARIES(glLua ${GL_LIBRARIES} ${LUA_LIBRARIES})
#endif()

if(WITH_GLM_PYTHON_WRAPPER)
    SWIG_ADD_MODULE(glmPython python glm.i)
    SWIG_LINK_LIBRARIES(glmPython ${GL_LIBRARIES} ${PYTHON_LIBRARIES})
endif()

################################################################################################
# Box2D
################################################################################################
set_source_files_properties(Box2D.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(Box2D.i PROPERTIES SWIG_FLAGS "")

if(WITH_BOX2D_LUA_WRAPPER)
    SWIG_ADD_MODULE(Box2DLua lua Box2D.i)
    SWIG_LINK_LIBRARIES(Box2DLua ${BOX2D_LIBRARIES} ${LUA_LIBRARIES})
endif()

if(WITH_BOX2D_PYTHON_WRAPPER)
    SWIG_ADD_MODULE(Box2DPython python Box2D.i)
    SWIG_LINK_LIBRARIES(Box2DPython ${BOX2D_LIBRARIES} ${PYTHON_LIBRARIES})
endif()


