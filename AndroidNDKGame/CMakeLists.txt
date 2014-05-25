cmake_minimum_required(VERSION 2.8)

set(NDKGAME NDKGame)
set(NDKGAME_CPP ${NDKGAME}_cpp)

set(NDKGAME_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/java)
set(NDKGAME_BIN_DIR ${CMAKE_BINARY_DIR}/${NDKGAME})
set(NDKGAME_LIBS_DIR ${NDKGAME_BIN_DIR}/libs/armeabi-v7a)

# Cpp part
include_directories(
    cpp
)
set(SOURCES
    cpp/main.cpp
    cpp/Engine/Sprite.cpp
    cpp/Engine/Texture.cpp
    cpp/Engine/Tools.cpp
    
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
)
add_library(${NDKGAME_CPP} SHARED ${SOURCES})

set(LIBS ${PNG_LIBRARIES} android log EGL GLESv1_CM)
target_link_libraries(${NDKGAME_CPP} ${LIBS})

# Java part
get_target_property(CPP_ ${NDKGAME_CPP} LOCATION)

add_custom_target(
    ${NDKGAME} ALL
    COMMAND
        # clean
        # rm -rf ${NDKGAME_BIN_DIR} && 
        
        # mkdir all project dirs
        mkdir -p ${NDKGAME_BIN_DIR} ${NDKGAME_LIBS_DIR} && #${NDKGAME_BIN_DIR}/src && 
        
        # copy symbolic link tree to binary directory
        ls ${NDKGAME_SRC_DIR} | xargs -I {} cp -rsf ${NDKGAME_SRC_DIR}/{} ${NDKGAME_BIN_DIR} && 
        
        # copy native library to libs dir
        cp ${CPP_} ${NDKGAME_LIBS_DIR} && 
        
        # update android library project 
        android update project -p ${NDKGAME_BIN_DIR} -s -t android-17 > /dev/null &&
        
        # go to project directory 
        cd ${NDKGAME_BIN_DIR} && 
        
        # and build it
        ant clean debug > /dev/null
    DEPENDS 
        ${NDKGAME_CPP}
)
