cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME QtLevelEditor)
project(${PROJECT_NAME})

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

#set(LIBS
#)
#target_link_libraries(${PROJECT_NAME} ${LIBS})
qt5_use_modules(QtLevelEditor Widgets Core)