/*
 * FireButton.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/FireButton.h>
#include <Game/Game.h>

using namespace ndk_game;
using namespace glm;
using namespace std;

FireButton::FireButton(int sw, int sh, BattleShip::Ptr bs): _bs(bs), _fadeOut(0)
{
    float w = sw * 0.18f,
            x = sw/2 - w/2,
            y = sh/2 - w/2;

    auto game = Game::instance();

    _norm = make_shared<Sprite>(
            game->getTexture("images/fire.png"),
            make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );

    auto m = _norm->getModelMatrix();
    m = translate(m, vec3(x, y, 0.f));

    _norm->getModelMatrix() = m;

    _pushed = make_shared<Sprite>(
            game->getTexture("images/fire_pushed.png"),
            make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );
    _pushed->getModelMatrix() = m;

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

FireButton::~FireButton()
{
    Log() << "FireButton::~FireButton()";
}

void FireButton::update(double elapsed) throw (runtime_error)
{
    if (_fadeOut >= 0)
    {
        _fadeOut -= elapsed;
    }
    else if (_cur == _pushed) _cur = _norm;
}

void FireButton::input(int x, int y) throw (runtime_error)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _pushed;

        if (!_bs) throw runtime_error("battle ship is null");
        _bs->fire();

        _fadeOut = 0.1f;
    }
}

list<ndk_game::Sprite::Ptr> FireButton::getSprites() const throw ()
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}

string FireButton::getName() const throw ()
{
    return "FireButton";
}
