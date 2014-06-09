/*
 * WinAgain.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#include <Game/WinAgain.h>
#include <Game/Rock.h>
#include <Game/Game.h>

using namespace ndk_game;
using namespace std;
using namespace glm;

WinAgain::WinAgain(android_app * app, int screenWidth)
{
    float winButtonW = screenWidth * 0.8, winButtonH = screenWidth * 0.4;

    _norm = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/win_again.png")),
            make_shared<RectSpriteLoader>(winButtonW, winButtonH, 1, 0.05, 0.95, 0.95, 0.52)
            );

    _pushed = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/win_again_pushed.png")),
            make_shared<RectSpriteLoader>(winButtonW, winButtonH, 1, 0.05, 0.95, 0.95, 0.52)
            );

    _pushed->getModelMatrix() = glm::translate(_pushed->getModelMatrix(),
            glm::vec3(2.f, -2.f, 0.f));

    _buttonRect = Rect(-winButtonW / 2, -winButtonH / 2, winButtonW / 2,
            winButtonH / 2);

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/white.png")),
            make_shared<RectSpriteLoader>(_buttonRect, 2, 0, 0.91, 1, 0.4)
            );
#endif

    _cur = _norm;
}

WinAgain::~WinAgain()
{
    Log() << "WinAgain::~WinAgain()";
}

void WinAgain::update(double elapsed) throw (std::runtime_error)
{
    if (_fadeOut >= 0)
    {
        _fadeOut -= elapsed;
    }
    else if (_cur == _pushed) _cur = _norm;
}

void WinAgain::input(int x, int y) throw (std::runtime_error)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _pushed;

        auto game = Game::instance();

        Rock::reset();
        game->newGame();
        game->getEngine()->setCurrentScene(game->getScene("Main"));

        _fadeOut = 0.1f;
    }
}

std::list<ndk_game::Sprite::Ptr> WinAgain::getSprites() const throw ()
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}

std::string WinAgain::getName() const throw ()
{
    return "YouWinAndTryAgain";
}
