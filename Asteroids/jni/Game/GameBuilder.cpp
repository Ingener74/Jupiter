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
#include <Game/Bullet.h>
#include <Game/Rock.h>

#include <Game/GameBuilder.h>

using namespace ndk_game;
using namespace std;
using namespace glm;

GameBuilder::GameBuilder(void *savedState, int savedStateSize, int screenWidth,
        int screenHeight, android_app* app): testSavedState(0)
{


    /*
     * 1. segfault in descructors
     *      Don't forget check Scene and start button shared cycle depened
     *
     *      06-01 10:00:46.712: V/threaded_app(11017): APP_CMD_TERM_WINDOW
     *      06-01 10:00:46.712: D/Asteroids(11017): GameBuilder::~GameBuilder()
     *      06-01 10:00:46.712: D/Asteroids(11017): StartButton::~StartButton()
     *      06-01 10:00:46.712: W/Adreno-ES20(11017): <core_glGetString:1654>: GL_INVALID_ENUM
     *      06-01 10:00:46.722: A/libc(11017): Fatal signal 11 (SIGSEGV) at 0xdeadbaad (code=1), thread 11045 (native_activity)
     *
     * 2. do key controlling more comfortably
     *
     * 3. play sound and back ground music
     *
     * 4. animate explosion
     *
     * 5. creating polygonal rocks
     *
     */

    if(savedStateSize > sizeof(int)){
        testSavedState = *static_cast<int *>(savedState);
        Log() << "Saved int " << testSavedState;
    }

    int w = screenWidth, h = screenHeight;

    Log() << "View port " << w << " x " << h;

    auto o = ortho<float>(-w / 2, w / 2, -h / 2, h / 2, -100, 100);

    drawEngine = make_shared<GLES20Engine>(
            make_shared<AssetShaderLoader>(app->activity->assetManager,
                    "shader/vertex.shader", "shader/fragment.shader"), o, w, h);

    /*
     * Create start scene
     */

    startScene = make_shared<Scene>();
    mainScene = make_shared<Scene>();
    winScene = make_shared<Scene>();
    failScene = make_shared<Scene>();

    auto backGround = make_shared<BackGround>(app, w);

    startScene->gameObject.push_back(backGround);
    mainScene->gameObject.push_back(backGround);

    startScene->gameObject.push_back(
            make_shared<StartButton>(app, w, drawEngine, mainScene));

    /*
     * Create main scene
     */
    auto battleShip = make_shared<BattleShip>(app, w, h, mainScene, failScene, drawEngine);

    mainScene->gameObject.push_back(battleShip);

    mainScene->gameObject.push_back(
            make_shared<FireButton>(app, w, h, battleShip));
    mainScene->gameObject.push_back(
            make_shared<RightButton>(app, w, h, battleShip));
    mainScene->gameObject.push_back(
            make_shared<LeftButton>(app, w, h, battleShip));
    mainScene->gameObject.push_back(
            make_shared<GasButton>(app, w, h, battleShip));

    mainScene->gameObject.push_back(
            make_shared<Rock>(app, w, h));
    mainScene->gameObject.push_back(
            make_shared<Rock>(app, w, h));

    winScene->gameObject.push_back(backGround);

    failScene->gameObject.push_back(backGround);

    drawEngine->setCurrentScene(startScene);
}

GameBuilder::~GameBuilder()
{
    Log() << "GameBuilder::~GameBuilder()";
}

tuple<void*, size_t> GameBuilder::saveGame()
{
    size_t savedStateSize = 0;
    uint8_t * savedState = new uint8_t[sizeof(testSavedState)];

    /*
     * Save game here
     */

    Log() << "Saving game to " << hex << reinterpret_cast<int>(savedState);

//    testSavedState += 10;

//    memcpy(savedState, &testSavedState, sizeof(testSavedState));

    Log() << "test saved";

    savedStateSize = sizeof(testSavedState);

    return tuple<void*, size_t>(savedState, savedStateSize);
}

IDrawEngine::Ptr GameBuilder::getEngine() const
        throw (runtime_error)
{
    if (!drawEngine) throw runtime_error("draw engine not created");
    return drawEngine;
}
