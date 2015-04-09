cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME GamePlayer)
project(${PROJECT_NAME})

include_directories(src/asteroids)

set(SOURCES
    src/GamePlayer.cpp
)

if(USE_FREEGLUT)
    set(SOURCES ${SOURCES} src/GlutMain.cpp)
elseif(USE_GLFW)
    set(SOURCES ${SOURCES} src/GLFWMain.cpp)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
    ${GL_LIBRARIES}
    ${Boost_LIBRARIES}
    ${PNG_LIBRARIES}
    #${LUA_LIBRARIES}
    
    #Ganymede
    Jupiter
)
target_link_libraries(${PROJECT_NAME} ${LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION Jupiter/bin)
