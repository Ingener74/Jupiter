cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME Jupiter)
project(${PROJECT_NAME})

set(SOURCES
    # Sound
    src/Sound/DummySound.cpp
    src/Sound/DummySoundEngine.cpp
    # Resources
    src/Resources/ResourceManager.cpp
    src/Resources/FStreamResource.cpp
    src/Resources/FileResource.cpp
    # Builders
    src/Builders/FileSpriteFactory.cpp
    src/Builders/ImageBuilder.cpp
    src/Builders/SpriteBuilder.cpp
    src/Builders/PNGImageFactory.cpp
    # Common
    src/ResourceShaderLoader.cpp
    src/SimpleShaderLoader.cpp
    src/Tools.cpp
    src/Game.cpp
    
    # Factories
    src/Factories/ImageTextureFactory.cpp
    
    src/Controller.cpp
    src/Node.cpp
    src/SpriteImpl.cpp
    src/TextureImpl.cpp
    
    # Graphics
    src/Graphics/Image.cpp
    src/Graphics/Rect.cpp
    src/Graphics/RectSpriteLoader.cpp
    src/Graphics/Scene.cpp
    src/Graphics/SimpleSpriteLoader.cpp
    src/Graphics/Sprite.cpp
    src/Graphics/Texture.cpp
    src/Graphics/TextureLoader.cpp
    src/Graphics/DrawEngine.cpp
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