cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME GamePlayer)
project(${PROJECT_NAME})

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
    GL
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${LUA_LIBRARIES}
    ${Boost_LIBRARIES}
)
target_link_libraries(${PROJECT_NAME} ${LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION Jupiter/bin)