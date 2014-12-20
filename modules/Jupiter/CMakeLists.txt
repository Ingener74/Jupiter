cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME Jupiter)
project(${PROJECT_NAME})

set(SOURCES
    # Sound
    src/Sound/DummySound.cpp
    src/Sound/DummySoundEngine.cpp

    src/ResourceManager.cpp
    src/FileResource.cpp
    
    src/Tools.cpp
    src/Game.cpp
    
    src/Graphics/Texture.cpp
    src/TextureImpl.cpp
    src/Builders/TextureBuilder.cpp
    src/Factories/ImageTextureFactory.cpp
    
    src/Graphics/Image.cpp
    src/ImageImpl.cpp
    src/Builders/ImageBuilder.cpp
    src/Builders/PNGImageFactory.cpp
    
    src/Node.cpp
    src/Shape.cpp
    src/NodeVisitor.cpp
    src/RenderVisitor.cpp
    
    src/Shader.cpp
    src/ShaderImpl.cpp
    src/FileShaderFactory.cpp
    
    src/Controller.cpp
    src/ControllerImpl.cpp
    src/CPPControllerFactory.cpp
    
    src/Graphics/Sprite.cpp
    
    # Old
    src/Graphics/Rect.cpp
    src/Graphics/RectSpriteLoader.cpp
    src/Graphics/Scene.cpp
    src/Graphics/SimpleSpriteLoader.cpp
    src/Graphics/DrawEngine.cpp
    src/ResourceShaderLoader.cpp
    src/SimpleShaderLoader.cpp
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
    ${Boost_LIBRARIES}
)
if(ANDROID)
    set(LIBS ${LIBS}
    )
else()
    set(LIBS ${LIBS}
    )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

target_link_libraries(${PROJECT_NAME} ${LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION Jupiter/lib)
install(DIRECTORY include DESTINATION Jupiter)