cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME GamePlayer)
project(${PROJECT_NAME})

include_directories(src/asteroids)

set(SOURCES
    src/main.cpp
    
    src/asteroids/BackGround.cpp
    src/asteroids/BattleShip.cpp
    src/asteroids/Bullet.cpp
    src/asteroids/Life.cpp
    # src/asteroids/FireButton.cpp
    # src/asteroids/GasButton.cpp
    # src/asteroids/LeftButton.cpp
    # src/asteroids/RightButton.cpp
    # src/asteroids/Rock.cpp
    # src/asteroids/StartButton.cpp
    # src/asteroids/WinAgain.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
    GL
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${Boost_LIBRARIES}
    
    lua
    Ganymede
    Jupiter
)
target_link_libraries(${PROJECT_NAME} ${LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION Jupiter/bin)