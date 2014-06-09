/*
 * LeftButton.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/LeftButton.h>
#include <Game/Game.h>

using namespace ndk_game;
using namespace glm;
using namespace std;

LeftButton::LeftButton(int screenWidth, int screenHeight, BattleShip::Ptr bs): _bs(bs), _fadeOut(0)
{
    float w = screenWidth * 0.18f, x = -screenWidth/2 + w/2, y = -screenHeight/2 + w/2;

    auto game = Game::instance();

    _norm = make_shared<Sprite>(
            game->getTexture("images/left.png"),
            make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );
    _norm->getModelMatrix() = translate(_norm->getModelMatrix(), vec3(x, y, 0.f));

    _pushed = make_shared<Sprite>(
            game->getTexture("images/left_pushed.png"),
            make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );
    _pushed->getModelMatrix() = translate(_pushed->getModelMatrix(), vec3(x, y, 0.f));

    float xt = x - 2, yt = y - 2;
    _buttonRect = Rect(xt - w/2, yt - w/2, xt + w/2, yt + w/2);

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(
            game->getTexture("images/white.png"),
            make_shared<RectSpriteLoader>(_buttonRect, 11, 0, 1, 0, 1)
            );
#endif

    _cur = _norm;
}

LeftButton::~LeftButton()
{
    Log() << "LeftButton::~LeftButton()";
}

void LeftButton::update(double elapsed) throw (runtime_error)
{
    if (_fadeOut >= 0)
    {
        _fadeOut -= elapsed;
    }
    else if (_cur == _pushed) _cur = _norm;
}

void LeftButton::input(int x, int y) throw (runtime_error)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _pushed;

        if (!_bs) throw runtime_error("battle ship is null");
        _bs->left();

        _fadeOut = 0.1f;
   }
}

list<ndk_game::Sprite::Ptr> LeftButton::getSprites() const throw ()
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}

string LeftButton::getName() const throw ()
{
    return "LeftButton";
}
