cmake_minimum_required(VERSION 2.8.11)


if(ANDROID)

    add_subdirectory(GamePlayerAndroid)

else()
    
    add_subdirectory(GameDesigner)
    
    add_subdirectory(GamePlayer)
    
endif()