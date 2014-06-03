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
        int screenHeight, android_app* app): testSavedState(0), _app(app),
                _screenWidth(screenWidth), _screenHeight(screenHeight)
{
    Rock::reset(); // hack ;)

    auto soundEngine = make_shared<SLESSoundEngine>(app);
    _background = soundEngine->loadSound("sounds/bgm.mp3");
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
    _rockTex = Texture::create(make_shared<AssetTextureLoader>(app, "images/rocks1.png"));

    auto battleShip = make_shared<BattleShip>(
            app, w, h, mainScene, failScene, drawEngine, make_shared<DummySoundEngine>());

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
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, make_shared<DummySoundEngine>(), _rockTex, vec3()).front());
    mainScene->gameObject.push_back(
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, make_shared<DummySoundEngine>(), _rockTex, vec3()).front());
    mainScene->gameObject.push_back(
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, make_shared<DummySoundEngine>(), _rockTex, vec3()).front());
    mainScene->gameObject.push_back(
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, make_shared<DummySoundEngine>(), _rockTex, vec3()).front());
    mainScene->gameObject.push_back(
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, make_shared<DummySoundEngine>(), _rockTex, vec3()).front());

    /*
     * Create win scene
     */
    winScene->gameObject.push_back(backGround);
    winScene->gameObject.push_back(
            make_shared<WinAgain>(app, w, drawEngine, mainScene, this));

    /*
     * Create fail scene
     */
    failScene->gameObject.push_back(backGround);
    failScene->gameObject.push_back(
            make_shared<GameAgain>(app, w, drawEngine, mainScene, this));

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

void GameBuilder::newGame()
{
    android_app* app = _app;
    int w = _screenWidth, h = _screenHeight;

    mainScene->gameObject.clear();

    auto backGround = make_shared<BackGround>(app, w);

    mainScene->gameObject.push_back(backGround);

    auto battleShip = make_shared<BattleShip>(
            app, w, h, mainScene, failScene, drawEngine, make_shared<DummySoundEngine>());

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
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, make_shared<DummySoundEngine>(), _rockTex, vec3()).front());
    mainScene->gameObject.push_back(
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, make_shared<DummySoundEngine>(), _rockTex, vec3()).front());
    mainScene->gameObject.push_back(
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, make_shared<DummySoundEngine>(), _rockTex, vec3()).front());
    mainScene->gameObject.push_back(
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, make_shared<DummySoundEngine>(), _rockTex, vec3()).front());
    mainScene->gameObject.push_back(
            Rock::createRock(app, w, h, drawEngine, winScene, mainScene, make_shared<DummySoundEngine>(), _rockTex, vec3()).front());
}
