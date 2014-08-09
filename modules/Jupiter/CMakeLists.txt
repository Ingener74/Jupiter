cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME Jupiter)
project(${PROJECT_NAME})

set(SOURCES
    src/DummySound.cpp
    src/DummySoundEngine.cpp
    src/DummyTextureLoader.cpp
    src/Image.cpp
    src/Rect.cpp
    src/RectSpriteLoader.cpp
    src/Scene.cpp
    src/SimpleShaderLoader.cpp
    src/SimpleSpriteLoader.cpp
    src/Sprite.cpp
    src/Texture.cpp
    src/TextureLoader.cpp
    src/Tools.cpp
    src/DrawEngine.cpp
    src/ResourceManager.cpp
)

if(ANDROID)
    set(SOURCES ${SOURCES}
        #src/AssetTextureLoader.cpp
        #src/SLESSound.cpp
        #src/SLESSoundEngine.cpp
    )
else()
    set(SOURCES ${SOURCES}
    )
endif()

add_library(${PROJECT_NAME} ${SOURCES})

set(LIBS
    ${PNG_LIBRARIES}
)
if(ANDROID)
    set(LIBS ${LIBS}
    )
else()
    set(LIBS ${LIBS}
    )
endif()

target_link_libraries(${PROJECT_NAME} ${LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION Jupiter/lib)
install(DIRECTORY include DESTINATION Jupiter)