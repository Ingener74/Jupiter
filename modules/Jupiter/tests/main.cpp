/*
 * main.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: pavel
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Jupiter.h"

using namespace std;
using namespace jupiter;

/**********************************************************************************************************************
 *
 * File tests
 *
 **********************************************************************************************************************/
static const char* RESOURCES_IMAGES_BG_PNG = "resources/images/bg.png";
static const char* RESOURCES_IMAGES_BULLET_PNG = "resources/images/bullet.png";

TEST(JupiterTest, Test1) {
    EXPECT_THROW( {
        File file{RESOURCES_IMAGES_BG_PNG};
    }, JupiterError);
}

TEST(JupiterTest, Test2) {
    auto bufferFactory = make_unique_<FileFactory>();
    File::setBufferFactory(bufferFactory.get());
    EXPECT_THROW({
        File file{RESOURCES_IMAGES_BG_PNG};
    }, JupiterError);
}

TEST(JupiterTest, Test3) {
    auto bufferFactory = make_unique_<FileFactory>();
    File::setBufferFactory(bufferFactory.get());
    File::setBase("../samples/Asteroids");
    EXPECT_NO_THROW({
        File file{RESOURCES_IMAGES_BG_PNG};
    });
}

TEST(JupiterTest, Test4) {
    File::setBufferFactory();
    EXPECT_THROW( {
        File file{RESOURCES_IMAGES_BG_PNG};
    }, JupiterError);
}

TEST(JupiterTest, Test5) {
    auto bufferFactory = make_unique_<FileFactory>();
    File::setBufferFactory(bufferFactory.get());
    EXPECT_NO_THROW({
        File file{RESOURCES_IMAGES_BG_PNG};
    });
}

/**********************************************************************************************************************
 *
 * PngImage tests
 *
 **********************************************************************************************************************/
TEST(JupiterTest, PngImage_Test1) {
    Image pngBackground = PngImage{RESOURCES_IMAGES_BG_PNG};
    EXPECT_EQ(pngBackground.getWidth(), 1024);
    EXPECT_EQ(pngBackground.getHeight(), 1024);
    EXPECT_EQ(pngBackground.getType(), Image::Type::RGB);
}

TEST(JupiterTest, PngImage_Test2) {
    Image pngBullet = PngImage{RESOURCES_IMAGES_BULLET_PNG};
    EXPECT_EQ(pngBullet.getWidth(), 128);
    EXPECT_EQ(pngBullet.getHeight(), 128);
    EXPECT_EQ(pngBullet.getType(), Image::Type::RGBA);
}

/**********************************************************************************************************************
 *
 * PngImage tests
 *
 **********************************************************************************************************************/
TEST(JupiterTest, JsonGame_Test1){
//    JsonGame jsonGame{"Asteroids.json"};
//
//    EXPECT_EQ(jsonGame.getWidth(),  800);
//    EXPECT_EQ(jsonGame.getHeight(), 480);
}

/**********************************************************************************************************************
 *
 * Node tests
 *
 **********************************************************************************************************************/
//TEST(JupiterTest, Test_setPositionX) {
//    auto n = Aware::get<Node>("test");
//    ASSERT_NE(n, nullptr);
//    ASSERT_EQ(n->setPosition(100.0, 0.0, 0.0)->getPositionX(), 100.0);
//}
