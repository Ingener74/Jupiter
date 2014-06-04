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

    Rock::reset(); // hack ;)

    Log() << "View port " << w << " x " << h;

    auto o = ortho<float>(-w / 2, w / 2, -h / 2, h / 2, -100, 100);

    _engine = make_shared<GLES20Engine>(
            make_shared<AssetShaderLoader>(a->activity->assetManager,
                    "shader/vertex.shader", "shader/fragment.shader"), o, w, h);

    auto backGround = make_shared<BackGround>(a, w);

    getScene("Start")->gameObject.push_back(backGround);
    getScene("Main")->gameObject.push_back(backGround);
    getScene("Fail")->gameObject.push_back(backGround);
    getScene("Win")->gameObject.push_back(backGround);

    getScene("Start")->gameObject.push_back(make_shared<StartButton>(w, h));

    newGame();


    _engine->setCurrentScene(getScene("Start"));
}

void Game::newGame()
{
}

void Game::stopGame()
{
}


Game::Game(): _app(0)
{
}
