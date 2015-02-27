/*
 * main.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: pavel
 */

#include <gtest/gtest.h>

#include <boost/filesystem.hpp>

#include "Jupiter.h"

using namespace std;
using namespace jupiter;
using namespace boost::filesystem;

class JupiterTest: public testing::Test {
public:
    void SetUp() {
    }

    void TearDown() {
    }
};

TEST(JupiterTest, Aware) {
    auto node = Aware::create<Node>("test");
    ASSERT_EQ(Aware::objectsCount(), 1);

    auto node1 = new Node("test2");
    ASSERT_EQ(Aware::objectsCount(), 2);
    ASSERT_EQ(Aware::get<Node>("test2"), node1);

    delete node1;
    ASSERT_EQ(Aware::objectsCount(), 1);
}

static const char* RESOURCES_IMAGES_BG_PNG = "resources/images/bg.png";
static const char* RESOURCES_IMAGES_BULLET_PNG = "resources/images/bullet.png";

TEST(JupiterTest, File_Test1) {
    EXPECT_THROW( {
        unique_ptr<File> file{new File(RESOURCES_IMAGES_BG_PNG)};
    }, JupiterError);
}

TEST(JupiterTest, File_Test2) {
    File::setBufferFactory(new LinuxFileFactory);
    EXPECT_THROW({
        unique_ptr<File> file{new File(RESOURCES_IMAGES_BG_PNG)};
    }, JupiterError);
}

TEST(JupiterTest, File_Test3) {
    File::setBufferFactory(new LinuxFileFactory);
    File::setBase("../samples/Asteroids");
    EXPECT_NO_THROW({
        unique_ptr<File> file(new File(RESOURCES_IMAGES_BG_PNG));
    });
}

TEST(JupiterTest, File_Test4) {
    File::setBufferFactory();
    EXPECT_THROW( {
        unique_ptr<File> file{new File(RESOURCES_IMAGES_BG_PNG)};
    }, JupiterError);
}

TEST(JupiterTest, File_Test5) {
    File::setBufferFactory(new LinuxFileFactory);
    EXPECT_NO_THROW({
        unique_ptr<File> file(new File(RESOURCES_IMAGES_BG_PNG));
    });
}

TEST(JupiterTest, PngImage_Test1) {
    auto pngBackground = Aware::create<PngImage>(RESOURCES_IMAGES_BG_PNG);
    ASSERT_EQ(pngBackground->getWidth(), 1024);
    ASSERT_EQ(pngBackground->getHeight(), 1024);
    ASSERT_EQ(pngBackground->getType(), Image::Type::RGB);
    ASSERT_EQ(pngBackground->getName(), RESOURCES_IMAGES_BG_PNG);
}

TEST(JupiterTest, PngImage_Test2) {
    auto pngBullet = Aware::create<PngImage>(RESOURCES_IMAGES_BULLET_PNG);
    ASSERT_EQ(pngBullet->getWidth(), 128);
    ASSERT_EQ(pngBullet->getHeight(), 128);
    ASSERT_EQ(pngBullet->getType(), Image::Type::RGBA);
    ASSERT_EQ(pngBullet->getName(), RESOURCES_IMAGES_BULLET_PNG);
}

TEST(JupiterTest, Node) {
    ASSERT_EQ(Aware::get<Node>("test")->setPosition(100.0, 0.0, 0.0)->getPositionX(), 100.0);
}

TEST(JupiterTest, JsonGame_Test1){
    unique_ptr<JsonGame> jsonGame(new JsonGame("Asteroids.json"));
}

TEST(JupiterTest, Aware_BalanceTest) {
    Aware::release();
    ASSERT_EQ(Object::objects, 0);
}

