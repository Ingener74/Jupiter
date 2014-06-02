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
#include <Game/GameAgain.h>
#include <Game/WinAgain.h>
#include <Game/Explosion.h>

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
     * 4. clean static variables
     *
     */

    auto soundEngine = make_shared<SLESSoundEngine>(app);

    auto explos = soundEngine->loadSound("sounds/explosion.mp3");
    explos->play();

    auto shot = soundEngine->loadSound("sounds/shot.mp3");
    shot->play();

    _background = soundEngine->loadSound("sounds/background.mp3");
    _background->play(true);

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
            make_shared<StartButton>(app, w, h, drawEngine, mainScene));

    /*
     * Create main scene / new game
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

    auto e = make_shared<Explosion>(app, w, h, 0, 0);

    mainScene->gameObject.push_back(
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, vec3()).front());
    mainScene->gameObject.push_back(
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, vec3()).front());

//    mainScene = newGame(app, w, h);

    /*
     * Create win scene
     */
    winScene->gameObject.push_back(backGround);
    winScene->gameObject.push_back(
            make_shared<WinAgain>(app, w, drawEngine, mainScene));

    /*
     * Create fail scene
     */
    failScene->gameObject.push_back(backGround);
    failScene->gameObject.push_back(
            make_shared<GameAgain>(app, w, drawEngine, mainScene));

    drawEngine->setCurrentScene(startScene);
}

GameBuilder::~GameBuilder()
{
    _background->stop();

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

ndk_game::Scene::Ptr GameBuilder::newGame(android_app* a, int sw, int sh)
{
    auto s = make_shared<Scene>();

//    auto battleShip = make_shared<BattleShip>(a, sw, sh, mainScene, failScene, drawEngine);
//
//    s->gameObject.push_back(battleShip);
//
//    s->gameObject.push_back(
//            make_shared<FireButton>(a, sw, sh, battleShip));
//    s->gameObject.push_back(
//            make_shared<RightButton>(a, sw, sh, battleShip));
//    s->gameObject.push_back(
//            make_shared<LeftButton>(a, sw, sh, battleShip));
//    s->gameObject.push_back(
//            make_shared<GasButton>(a, sw, sh, battleShip));
//
//    s->gameObject.push_back(
//            make_shared<Rock>(a, sw, sh, drawEngine, winScene, mainScene));
//    s->gameObject.push_back(
//            make_shared<Rock>(a, sw, sh, drawEngine, winScene, mainScene));

    return s;
}
