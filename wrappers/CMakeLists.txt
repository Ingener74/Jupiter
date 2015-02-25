cmake_minimum_required(VERSION 2.8.11)

find_package(SWIG)
include(${SWIG_USE_FILE})

find_package(PythonLibs)
include_directories(
    ${PYTHON_INCLUDE_PATH} 
    .
)

set(CMAKE_SWIG_FLAGS "-c++")

SET_SOURCE_FILES_PROPERTIES(Jupiter.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(Jupiter.i PROPERTIES SWIG_FLAGS "-includeall")

# Python
SWIG_ADD_MODULE(PyJupiter python Jupiter.i)
SWIG_LINK_LIBRARIES(PyJupiter ${PYTHON_LIBRARIES} Jupiter GL ${GLEW_LIBRARIES} ${Boost_LIBRARIES})

# Lua
SWIG_ADD_MODULE(LuaJupiter lua Jupiter.i)
SWIG_LINK_LIBRARIES(LuaJupiter Jupiter GL ${GLEW_LIBRARIES} ${Boost_LIBRARIES})
