cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME Jupiter)
project(${PROJECT_NAME})

set(SOURCES
    src/Jupiter.cpp
    
    src/RCO.cpp
    src/Ref.cpp
    
    src/File.cpp
    src/FileFactory.cpp
    
    src/Game.cpp
    
    src/Tools.cpp
    src/Texture.cpp
    src/ImageTexture.cpp

    src/Image.cpp
    src/PngImage.cpp
    
    src/Node.cpp
    src/Transform.cpp
    
    src/Shape.cpp
    src/VertexComponent.cpp
    src/ImageShape.cpp
    
    src/Sprite.cpp
    src/DrawNode.cpp

    src/Camera.cpp
    src/NodeVisitor.cpp
    src/RenderVisitor.cpp
    src/PrintVisitor.cpp

    src/Shader.cpp
    src/Attribute.cpp
    src/Uniform.cpp
    src/FileShader.cpp

    src/Listener.cpp
    src/MoveListener.cpp
    src/ScaleListener.cpp
    src/CollisionListener.cpp
    src/RotationListener.cpp
    src/KeyboardListener.cpp
    
    src/Body.cpp
    # src/SpriteBody.cpp
    src/Physics/Box2D/VisualBody.cpp
    
    src/Physics.cpp
    
    src/PhysicsShape.cpp
    src/PoligonShape.cpp
    src/CircleShape.cpp
    src/ComplexShape.cpp
    
    src/Physics/Box2D/PhysicsBodyEditorAtlas.cpp
    
    src/Physics/Box2D/Joint.cpp
    src/Physics/Box2D/RevoluteJoint.cpp
    src/Physics/Box2D/DistanceJoint.cpp
    src/Physics/Box2D/RopeJoint.cpp
    src/Physics/Box2D/GearJoint.cpp
    src/Physics/Box2D/MotorJoint.cpp
    src/Physics/Box2D/WheelJoint.cpp
    src/Physics/Box2D/FrictionJoint.cpp
    src/Physics/Box2D/MouseJoint.cpp
    src/Physics/Box2D/PrismaticJoint.cpp
    src/Physics/Box2D/PulleyJoint.cpp
    src/Physics/Box2D/WeldJoint.cpp
    
    src/Animations/Animation.cpp
    src/Animations/MoveAnimation.cpp
)

if(ANDROID)
elseif(MINGW)
    set(SOURCES ${SOURCES} 
        src/File-default.cpp
        src/JupiterError-win32.cpp
    )
elseif(EMSCRIPTEN)
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

#
#  В тестах для тестирования приватных членов делать 
#  #define private public
#  подсмотрено здесь https://github.com/nlohmann/json/blob/master/test/unit.cpp
# 

# TODO if jupiter shader, then link
set(LIBS
    ${OPENGL_LIBRARIES}
    ${GLEW_LIB}
    lodepng
)
target_link_libraries(${PROJECT_NAME} lodepng ${LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION Jupiter/lib)
install(DIRECTORY include DESTINATION Jupiter)

add_executable(JupiterTests tests/main.cpp)
target_link_libraries(JupiterTests Jupiter gmock gtest pthread gmock_main gtest_main)



