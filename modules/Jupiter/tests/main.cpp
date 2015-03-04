/*
 * main.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: pavel
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/filesystem.hpp>

#include "Jupiter.h"

using namespace std;
using namespace jupiter;
using namespace boost::filesystem;

TEST(JupiterTest, Aware) {
    auto node = Aware::create<Node>("test");
    ASSERT_EQ(Aware::objectsCount(), 1);

    {
        unique_ptr<Node> node1{new Node("test2")};
        ASSERT_EQ(Aware::objectsCount(), 2);
        ASSERT_EQ(Aware::get<Node>("test2"), node1.get());
    }

    ASSERT_EQ(Aware::objectsCount(), 1);
}

/**********************************************************************************************************************
 *
 * File tests
 *
 **********************************************************************************************************************/
static const char* RESOURCES_IMAGES_BG_PNG = "resources/images/bg.png";
static const char* RESOURCES_IMAGES_BULLET_PNG = "resources/images/bullet.png";

TEST(FileTest, Test1) {
    EXPECT_THROW( {
        unique_ptr<File> file{new File(RESOURCES_IMAGES_BG_PNG)};
    }, JupiterError);
}

TEST(FileTest, Test2) {
    File::setBufferFactory(new LinuxFileFactory);
    EXPECT_THROW({
        unique_ptr<File> file{new File(RESOURCES_IMAGES_BG_PNG)};
    }, JupiterError);
}

TEST(FileTest, Test3) {
    File::setBufferFactory(new LinuxFileFactory);
    File::setBase("../samples/Asteroids");
    EXPECT_NO_THROW({
        unique_ptr<File> file(new File(RESOURCES_IMAGES_BG_PNG));
    });
}

TEST(FileTest, Test4) {
    File::setBufferFactory();
    EXPECT_THROW( {
        unique_ptr<File> file{new File(RESOURCES_IMAGES_BG_PNG)};
    }, JupiterError);
}

TEST(FileTest, Test5) {
    File::setBufferFactory(new LinuxFileFactory);
    EXPECT_NO_THROW({
        unique_ptr<File> file(new File(RESOURCES_IMAGES_BG_PNG));
    });
}

/**********************************************************************************************************************
 *
 * PngImage tests
 *
 **********************************************************************************************************************/
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

/**********************************************************************************************************************
 *
 * PngImage tests
 *
 **********************************************************************************************************************/
TEST(JupiterTest, JsonGame_Test1){
    unique_ptr<JsonGame> jsonGame(new JsonGame("Asteroids.json"));

    ASSERT_EQ(jsonGame->getWidth(),  800);
    ASSERT_EQ(jsonGame->getHeight(), 480);
}

/**********************************************************************************************************************
 *
 * Node tests
 *
 **********************************************************************************************************************/
TEST(NodeTest, Test_setPositionX) {
    auto n = Aware::get<Node>("test");
    ASSERT_NE(n, nullptr);
    ASSERT_EQ(n->setPosition(100.0, 0.0, 0.0)->getPositionX(), 100.0);
}

/**********************************************************************************************************************
 *
 * Controller tests
 *
 **********************************************************************************************************************/
class MockController: public Controller {
public:
    MOCK_METHOD1(onVisibleChanged, void(bool isVisible));

    MOCK_METHOD3(onMove, void(float x, float y, float z));
    MOCK_METHOD3(onPositionChanged, void(float x, float y, float z));

    MOCK_METHOD3(onScale, void (float x, float y, float z));
    MOCK_METHOD3(onScaleChanged, void (float x, float y, float z));

    MOCK_METHOD3(onRotate, void (float x, float y, float z));
    MOCK_METHOD3(onRotationChanged, void (float x, float y, float z));

    MOCK_METHOD1(update, void (double elapsedTime));
};

class ControllerTest: public testing::Test {
public:
    void SetUp() {
        n.setController(&c);
    }

    void TearDown() {
    }

    Node n{"testController"};
    MockController c;
};

TEST_F(ControllerTest, Test_positionChangedX){
    EXPECT_CALL(c, onPositionChanged(100.f, 0.f, 0.f)).Times(1);
    n.setPositionX(100.f);
}

TEST_F(ControllerTest, Test_positionChangedY){
    EXPECT_CALL(c, onPositionChanged(0.f, 100.f, 0.f)).Times(1);
    n.setPositionY(100.f);
}

TEST_F(ControllerTest, Test_positionChangedZ){
    EXPECT_CALL(c, onPositionChanged(0.f, 0.f, 100.f)).Times(1);
    n.setPositionZ(100.f);
}

TEST_F(ControllerTest, Test_positionChanged){
    EXPECT_CALL(c, onPositionChanged(10.f, 20.f, 30.f)).Times(1);
    n.setPosition(10.f, 20.f, 30.f);
}

TEST_F(ControllerTest, Test_moveX){
    EXPECT_CALL(c, onMove(100.f, 0.f, 0.f)).Times(1);
    n.translateX(100.f);
}

TEST_F(ControllerTest, Test_moveY){
    EXPECT_CALL(c, onMove(0.f, 100.f, 0.f)).Times(1);
    n.translateY(100.f);
}

TEST_F(ControllerTest, Test_moveZ){
    EXPECT_CALL(c, onMove(0.f, 0.f, 100.f)).Times(1);
    n.translateZ(100.f);
}

TEST_F(ControllerTest, Test_move){
    EXPECT_CALL(c, onMove(10.f, 20.f, 30.f)).Times(1);
    n.translate(10.f, 20.f, 30.f);
}

TEST_F(ControllerTest, Test_scaleX){
    EXPECT_CALL(c, onScale(10.f, 0.f, 0.f)).Times(1);
    n.scaleX(10.f);
}

TEST_F(ControllerTest, Test_scaleY){
    EXPECT_CALL(c, onScale(0.f, 10.f, 0.f)).Times(1);
    n.scaleY(10.f);
}

TEST_F(ControllerTest, Test_scale){
    EXPECT_CALL(c, onScale(10.f, 20.f, 0.f)).Times(1);
    n.scale(10.f, 20.f);
}

TEST_F(ControllerTest, Test_scaleChangedX){
    EXPECT_CALL(c, onScaleChanged(10.f, 0.f, 0.f)).Times(1);
    n.setScaleX(10.f);
}

TEST_F(ControllerTest, Test_scaleChangedY){
    EXPECT_CALL(c, onScaleChanged(0.f, 10.f, 0.f)).Times(1);
    n.setScaleY(10.f);
}

TEST_F(ControllerTest, Test_scaleChanged){
    EXPECT_CALL(c, onScaleChanged(10.f, 20.f, 0.f)).Times(1);
    n.setScale(10.f, 20.f);
}

TEST_F(ControllerTest, Test_visibleChangedTrue){
    EXPECT_CALL(c, onVisibleChanged(true)).Times(1);
    n.setVisible(true);
}

TEST_F(ControllerTest, Test_visibleChangedFalse){
    EXPECT_CALL(c, onVisibleChanged(false)).Times(1);
    n.setVisible(false);
}

TEST_F(ControllerTest, Test_rotateX){
    EXPECT_CALL(c, onRotate(1.f, 0.f, 0.f)).Times(1);
    n.rotateX(1.f);
}

TEST_F(ControllerTest, Test_rotateY){
    EXPECT_CALL(c, onRotate(0.f, 1.f, 0.f)).Times(1);
    n.rotateY(1.f);
}

TEST_F(ControllerTest, Test_rotateZ){
    EXPECT_CALL(c, onRotate(0.f, 0.f, 1.f)).Times(1);
    n.rotateZ(1.f);
}

TEST_F(ControllerTest, Test_rotate){
    EXPECT_CALL(c, onRotate(1.f, 2.f, 3.f)).Times(1);
    n.rotate(1.f, 2.f, 3.f);
}

TEST_F(ControllerTest, Test_rotateChangedX){
    EXPECT_CALL(c, onRotationChanged(1.f, 0.f, 0.f)).Times(1);
    n.setRotationX(1.f);
}

TEST_F(ControllerTest, Test_rotateChangedY){
    EXPECT_CALL(c, onRotationChanged(0.f, 1.f, 0.f)).Times(1);
    n.setRotationY(1.f);
}

TEST_F(ControllerTest, Test_rotateChangedZ){
    EXPECT_CALL(c, onRotationChanged(0.f, 0.f, 1.f)).Times(1);
    n.setRotationZ(1.f);
}

TEST_F(ControllerTest, Test_rotateChanged){
    EXPECT_CALL(c, onRotationChanged(1.f, 0.f, 0.f)).Times(1);
    n.setRotation(1.f, 2.f, 3.f);
}

/**********************************************************************************************************************
 *
 * Aware objects leak test
 *
 **********************************************************************************************************************/
TEST(JupiterTest, Aware_BalanceTest) {
    Aware::release();
    ASSERT_EQ(Object::objects, 0);
}

