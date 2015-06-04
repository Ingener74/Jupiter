cmake_minimum_required(VERSION 2.8.11)


if(ANDROID)

    add_subdirectory(GamePlayerAndroid)

else()
    
    if(WITH_GAME_PLAYER)
        add_subdirectory(Callisto)
    endif()

    add_subdirectory(Test)
    
    add_executable(ref_test Ref/main.cpp Ref/RCO.cpp)
    
    add_definitions(-fPIC)
    add_library(json_test_lib Json/test.cpp)
    add_executable(json_test Json/main.cpp)
    target_link_libraries(json_test json_test_lib)

    find_package(SWIG)
    include(${SWIG_USE_FILE})
    
    find_package(PythonLibs 2.7 REQUIRED)
    include_directories(
        ${PYTHON_INCLUDE_PATH} 
        Json
    )
    
    set(CMAKE_SWIG_FLAGS "-c++")
    
    set_source_files_properties(Json/json.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(Json/json.i PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")
    
    set(CMAKE_SWIG_OUTDIR ${CMAKE_BINARY_DIR}/bin)
    
    SWIG_ADD_MODULE(jsonPython python Json/json.i)
    SWIG_LINK_LIBRARIES(jsonPython json_test_lib ${PYTHON_LIBRARIES})
endif()
