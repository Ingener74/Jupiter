/*
 * GameAgain.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#include <Game/GameAgain.h>
#include <Game/Rock.h>

using namespace ndk_game;
using namespace std;
using namespace glm;

GameAgain::GameAgain(android_app * app, int screenWidth,
        weak_ptr<ndk_game::IDrawEngine> engine,
        weak_ptr<ndk_game::Scene> mainScene,
        GameBuilder* game):
        _engine(engine), _mainScene(mainScene), _fadeOut(0), _game(game)
{
    float againButtonW = screenWidth * 0.8, againButtonH = screenWidth * 0.4;

    _norm = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/fail_again.png")),
            make_shared<RectSpriteLoader>(againButtonW, againButtonH, 1, 0.05, 0.95, 0.95, 0.52)
            );

    _pushed = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/fail_again_pushed.png")),
            make_shared<RectSpriteLoader>(againButtonW, againButtonH, 1, 0.05, 0.95, 0.95, 0.52)
            );

    _pushed->getModelMatrix() = glm::translate(_pushed->getModelMatrix(),
            glm::vec3(2.f, -2.f, 0.f));

    _buttonRect = Rect(-againButtonW / 2, -againButtonH / 2, againButtonW / 2,
            againButtonH / 2);

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/white.png")),
            make_shared<RectSpriteLoader>(_buttonRect, 2, 0, 0.91, 1, 0.4)
            );
#endif

    _cur = _norm;
}

GameAgain::~GameAgain()
{
    Log() << "GameAgain::~GameAgain()";
}

void GameAgain::update(double elapsed) throw (runtime_error)
{
    if (_fadeOut >= 0)
    {
        _fadeOut -= elapsed;
    }
    else if (_cur == _pushed) _cur = _norm;
}

void GameAgain::input(int x, int y) throw (runtime_error)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _pushed;

        Rock::reset();
        _game->newGame();
        if(auto e = _engine.lock())e->setCurrentScene(_mainScene.lock());

        _fadeOut = 0.1f;
    }
}

list<ndk_game::Sprite::Ptr> GameAgain::getSprites() const throw ()
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}

string GameAgain::getName() const throw ()
{
    return "GageAgain";
}
