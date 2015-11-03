cmake_minimum_required(VERSION 2.8.11)


if(ANDROID)

    add_subdirectory(GamePlayerAndroid)

else()
    
    if(WITH_TEST_PROGRAMS)
        add_subdirectory(Test)
    endif()
    
    if(WITH_CALLISTO)
        add_subdirectory(Callisto)
    endif()

    option(WITH_FREETYPE_TEST "With FreeType test" OFF)
    if(WITH_FREETYPE_TEST)
        add_executable(freetype_test FreeType/main.cpp)
        target_link_libraries(freetype_test ${FREETYPE_LIB})
    endif()
    
endif()
