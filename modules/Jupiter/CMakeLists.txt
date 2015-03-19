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

    src/Image.cpp
    src/PngImage.cpp
    
    src/Node.cpp
    src/JsonNode.cpp
    
    src/Shape.cpp
    src/Sprite.cpp
    src/JsonSprite.cpp

    src/NodeVisitor.cpp
    src/RenderVisitor.cpp

    src/Shader.cpp
    src/Controller.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

set(LIBS
    ${GL_LIBRARIES}
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

add_executable(Jupiter_test tests/main.cpp)
target_link_libraries(Jupiter_test Jupiter gtest gtest_main gmock GL)
add_test(AllTestsInJupiter Jupiter_test)

install(TARGETS ${PROJECT_NAME} DESTINATION Jupiter/lib)
install(DIRECTORY include DESTINATION Jupiter)