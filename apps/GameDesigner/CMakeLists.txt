cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME GameDesigner)
project(${PROJECT_NAME})

include_directories(src)

qt5_add_resources(RES_SOURCES res/GameDesigner.qrc)
qt5_wrap_ui(UI_SOURCES ui/GameDesigner.ui)

set(SOURCES
    src/main.cpp
    src/GameDesigner.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${UI_SOURCES} ${RES_SOURCES})

qt5_use_modules(GameDesigner Widgets Core)