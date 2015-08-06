cmake_minimum_required(VERSION 2.8.11)


if(ANDROID)

    add_subdirectory(GamePlayerAndroid)

else()
    
    if(WITH_GAME_PLAYER)
        add_subdirectory(Callisto)
    endif()

    if(WITH_TEST_PROGRAMS)
        add_subdirectory(Test)
    endif()
    
    
    option(WITH_FREETYPE_TEST "With FreeType test" OFF)
    if(WITH_FREETYPE_TEST)
        find_package(Freetype REQUIRED)
        include_directories(
            ${FREETYPE_INCLUDE_DIRS}
        )
        add_executable(freetype_test FreeType/main.cpp)
        target_link_libraries(freetype_test ${FREETYPE_LIBRARIES})
    endif()
    
endif()
