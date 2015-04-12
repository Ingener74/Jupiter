cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME Jupiter)
project(${PROJECT_NAME})

set(SOURCES
    src/File.cpp
    src/LinuxFileFactory.cpp
    
    src/Game.cpp
    src/JsonGame.cpp
    
    src/Tools.cpp
    src/Texture.cpp
    src/ImageTexture.cpp

    src/Image.cpp
    src/PngImage.cpp
    
    src/Node.cpp
    src/JsonNode.cpp
    
    src/Shape.cpp
    src/VertexComponent.cpp
    src/ImageShape.cpp
    
    src/Sprite.cpp
    src/JsonSprite.cpp

    src/NodeVisitor.cpp
    src/RenderVisitor.cpp
    src/PrintVisitor.cpp

    src/Shader.cpp
    src/Attribute.cpp
    src/Uniform.cpp
    src/FileShader.cpp

    src/Controller.cpp
)

if(ANDROID)
else()
    set(SOURCES ${SOURCES} src/File-default.cpp)
endif()

add_library(${PROJECT_NAME} ${SOURCES})

set(LIBS
    ${GL_LIBRARIES}
    ${PNG_LIBRARIES}
    ${Boost_LIBRARIES}
    lodepng
)
if(ANDROID)
    set(LIBS ${LIBS}
    )
else()
    set(LIBS ${LIBS}
    )
endif()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

add_definitions(-fPIC)
target_link_libraries(${PROJECT_NAME} ${LIBS})

if(WITH_TESTS)
    add_executable(Jupiter_test tests/main.cpp)
    target_link_libraries(Jupiter_test Jupiter gtest gtest_main gmock ${GL_LIBRARIES})
    add_test(AllTestsInJupiter Jupiter_test)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION Jupiter/lib)
install(DIRECTORY include DESTINATION Jupiter)