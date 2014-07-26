cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME QtLevelEditor)
project(${PROJECT_NAME})

qt5_add_resources(RES_SOURCES res/QtLevelEditor.qrc)
qt5_wrap_ui(UI_SOURCES ui/QtLevelEditor.ui)

set(SOURCES
    src/main.cpp
    src/LevelEditor.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${UI_SOURCES} ${RES_SOURCES})

#set(LIBS
#)
#target_link_libraries(${PROJECT_NAME} ${LIBS})
qt5_use_modules(QtLevelEditor Widgets Core)