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
set_source_files_properties(Jupiter.i PROPERTIES SWIG_FLAGS "-includeall")
#set_source_files_properties(Jupiter.i PROPERTIES SWIG_FLAGS "-v") # swig verbose

set(SHARED_LIBS
    Jupiter 
    GL 
    ${GLEW_LIBRARIES} 
    ${Boost_LIBRARIES}
)

# Lua
if(WITH_LUA_WRAPPER)
    SWIG_ADD_MODULE(LuaJupiter lua Jupiter.i)
    SWIG_LINK_LIBRARIES(LuaJupiter ${SHARED_LIBS})
endif()

# Python
if(WITH_PYTHON_WRAPPER)
    SWIG_ADD_MODULE(PyJupiter python Jupiter.i)
    SWIG_LINK_LIBRARIES(PyJupiter ${SHARED_LIBS} ${PYTHON_LIBRARIES})
endif()