cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME Jupiter)
project(${PROJECT_NAME})

set(SOURCES
    src/Jupiter.cpp

    src/File.cpp
    src/FileFactory.cpp
    
    src/Game.cpp
#    src/JsonGame.cpp
    
    src/Tools.cpp
    src/Texture.cpp
    src/ImageTexture.cpp

    src/Image.cpp
    src/PngImage.cpp
    
    src/Node.cpp
#    src/JsonNode.cpp
    
    src/Shape.cpp
    src/VertexComponent.cpp
    src/ImageShape.cpp
    
    src/Sprite.cpp
#    src/JsonSprite.cpp

    src/Camera.cpp
    src/NodeVisitor.cpp
    src/RenderVisitor.cpp
    src/PrintVisitor.cpp
    

    src/Shader.cpp
    src/Attribute.cpp
    src/Uniform.cpp
    src/FileShader.cpp

    src/Controller.cpp

    src/Listener.cpp
    src/MoveListener.cpp
    src/ScaleListener.cpp
    src/CollisionListener.cpp
    src/RotationListener.cpp
    src/KeyboardListener.cpp
    
    src/Box2dNode.cpp
    src/Box2dVisitor.cpp
    
    src/SpriteBox2d.cpp
    
    src/PhysicsShape.cpp
    src/PoligonShape.cpp
)

if(ANDROID)
elseif(MINGW)
    set(SOURCES ${SOURCES} 
        src/File-default.cpp
        src/JupiterError-win32.cpp
    )
else()
    set(SOURCES ${SOURCES} 
        src/File-default.cpp
        src/JupiterError-linux.cpp
    )
endif()

if(MINGW)
else()
    add_definitions(-fPIC)
endif()


add_library(${PROJECT_NAME} ${SOURCES})

set(LIBS
    ${GL_LIBRARIES}
    ${PNG_LIBRARIES}
    ${BOX2D_LIBRARIES}
    lodepng
)

target_link_libraries(${PROJECT_NAME} ${LIBS})

if(WITH_TESTS)
    add_executable(Jupiter_test tests/main.cpp)
    target_link_libraries(Jupiter_test Jupiter gtest gtest_main gmock ${GL_LIBRARIES})
    add_test(AllTestsInJupiter Jupiter_test)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION Jupiter/lib)
install(DIRECTORY include DESTINATION Jupiter)