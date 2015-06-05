cmake_minimum_required(VERSION 2.8.11)


if(ANDROID)

    add_subdirectory(GamePlayerAndroid)

else()
    
    if(WITH_GAME_PLAYER)
        add_subdirectory(Callisto)
    endif()

    add_subdirectory(Test)
    
    add_executable(ref_test Ref/main.cpp Ref/RCO.cpp)
endif()
