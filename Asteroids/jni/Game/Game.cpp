/*
 * Game.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: pavel
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
#include <Game/Life.h>

#include <Game/Game.h>

using namespace ndk_game;
using namespace std;
using namespace glm;

Game::Ptr Game::_self;

Game::Ptr Game::instance()
{
    if (!_self) _self = Game::Ptr(new Game);
    return _self;
}

void Game::reset()
{
    _self.reset();
}

Game::~Game()
{
    Log() << "Game::~Game()";
}

Scene::Ptr Game::getScene(const string& sceneName)
{
    Scene::Ptr s = _scenes[sceneName];
    if (!s)
    {
        s = make_shared<Scene>();
        _scenes[sceneName] = s;
    }
    return s;
}

ndk_game::Texture::Ptr Game::getTexture(const std::string& textureFile)
{
    Texture::Ptr t = _textures[textureFile];
    if (!t)
    {
        t = Texture::create(make_shared<AssetTextureLoader>(_app, textureFile));
        _textures[textureFile] = t;
    }
    return t;
}

IDrawEngine::Ptr Game::getEngine()
{
    return _engine;
}

void Game::startGame(android_app* a, int w, int h)
{
    _app = a;
    _screenWidth = w;
    _screenHeight = h;

    Rock::reset(); // hack ;)

    Log() << "View port " << w << " x " << h;

    auto o = ortho<float>(-w / 2, w / 2, -h / 2, h / 2, -100, 100);

    _engine = make_shared<GLES20Engine>(
            make_shared<AssetShaderLoader>(a->activity->assetManager,
                    "shader/vertex.shader", "shader/fragment.shader"), o, w, h);

    auto backGround = make_shared<BackGround>(a, w);

    auto startScene = getScene("Start");
    startScene->gameObject.push_back(backGround);
    startScene->gameObject.push_back(make_shared<StartButton>(w, h));
    _engine->setCurrentScene(startScene);

    auto failScene = getScene("Fail");
    failScene->gameObject.push_back(backGround);
    failScene->gameObject.push_back(make_shared<GameAgain>(_app, w));

    auto winScene = getScene("Win");
    winScene->gameObject.push_back(backGround);
    winScene->gameObject.push_back(make_shared<WinAgain>(_app, w));

    newGame();
}

void Game::newGame()
{
    auto ms = getScene("Main");
    ms->gameObject.clear();

    auto w = _screenWidth, h = _screenHeight;

    ms->gameObject.push_back(make_shared<BackGround>(_app, w));

    auto dse = make_shared<DummySoundEngine>();

    auto l = make_shared<Life>(w, h);

    auto bs = make_shared<BattleShip>(w, h, l, dse);

    ms->gameObject.push_back( Rock::createRock(w, h, dse, vec3()).front() );
    ms->gameObject.push_back( Rock::createRock(w, h, dse, vec3()).front() );
    ms->gameObject.push_back( Rock::createRock(w, h, dse, vec3()).front() );

    ms->gameObject.push_back(bs);
    ms->gameObject.push_back(make_shared<FireButton>(w, h, bs));
    ms->gameObject.push_back(make_shared<GasButton>(w, h, bs));
    ms->gameObject.push_back(make_shared<RightButton>(w, h, bs));
    ms->gameObject.push_back(make_shared<LeftButton>(w, h, bs));
    ms->gameObject.push_back(l);
}

void Game::stopGame()
{
}

Game::Game()
{
}
