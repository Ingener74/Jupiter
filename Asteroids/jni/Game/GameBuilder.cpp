/*
 * GameBuilder.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/AssetShaderLoader.h>
#include <Game/BackGround.h>
#include <Game/StartButton.h>
#include <Game/BattleShip.h>
#include <Game/FireButton.h>
#include <Game/RightButton.h>
#include <Game/LeftButton.h>
#include <Game/GasButton.h>
#include <Game/GameBuilder.h>

using namespace ndk_game;

GameBuilder::GameBuilder(void *savedState, int savedStateSize, int screenWidth,
        int screenHeight, android_app* app): testSavedState(0)
{
    if(savedStateSize > sizeof(int)){
        testSavedState = *static_cast<int *>(savedState);
        Log() << "Saved int " << testSavedState;
    }

    int w = screenWidth, h = screenHeight;

    Log() << "View port " << w << " x " << h;

    glm::mat4 ortho = glm::ortho<float>(-w / 2, w / 2, -h / 2, h / 2, -100,
            100);

    drawEngine = std::make_shared<GLES20Engine>(
            std::make_shared<AssetShaderLoader>(app->activity->assetManager,
                    "shader/vertex.shader", "shader/fragment.shader"), ortho, w,
            h);

    /*
     * Create start scene
     */

    startScene = std::make_shared<Scene>();
    mainScene = std::make_shared<Scene>();

    auto backGround = std::make_shared<BackGround>(app, w);

    startScene->gameObject.push_back(backGround);
    mainScene->gameObject.push_back(backGround);

    startScene->gameObject.push_back(
            std::make_shared<StartButton>(app, w, drawEngine, mainScene));

    /*
     * Create main scene
     */
    auto battleShip = std::make_shared<BattleShip>(app, w);

    mainScene->gameObject.push_back(battleShip);

    mainScene->gameObject.push_back(
            std::make_shared<FireButton>(app, w, h, battleShip));
    mainScene->gameObject.push_back(
            std::make_shared<RightButton>(app, w, h, battleShip));
    mainScene->gameObject.push_back(
            std::make_shared<LeftButton>(app, w, h, battleShip));
    mainScene->gameObject.push_back(
            std::make_shared<GasButton>(app, w, h, battleShip));

    /*
     *
     *           1
     *           0 R
     *
     *
     *          0 0
     *
     *
     * 2                   3
     * -R -R               R -R
     */
    float R = 100.3f,
            rV[]
            { 0.f, R, 1.f, 0.1f, 0.4f, -R, -R, 1.f, 0.2f, 0.5f, R, -R, 1.f,
                    0.1f, 0.2f };
    auto rock1 = std::make_shared<Sprite>(
            Texture::create(
                    std::make_shared<AssetTextureLoader>(app,
                            "images/rocks.png")),
            std::make_shared<SimpleSpriteLoader>(rV, 3));
//        mainScene->gameObject.push_back(rock1);

    drawEngine->setCurrentScene(startScene);
}

GameBuilder::~GameBuilder()
{
}

std::tuple<void*, int> GameBuilder::saveGame()
{
    uint8_t * savedState = new uint8_t[sizeof(testSavedState)];
    int savedStateSize = 0;

    /*
     * Save game here
     */

    Log() << "Saving game to " << savedState;

    testSavedState += 10;

//    *(reinterpret_cast<int*>(savedState)) = testSavedState;
    memcpy(savedState, &testSavedState, sizeof(testSavedState));

    Log() << "test saved";

    savedStateSize = sizeof(testSavedState);

    return std::tuple<void*, int>(savedState, savedStateSize);
}

ndk_game::IDrawEngine::Ptr GameBuilder::getEngine() const
        throw (std::runtime_error)
{
    if (!drawEngine) throw std::runtime_error("draw engine not created");
    return drawEngine;
}
