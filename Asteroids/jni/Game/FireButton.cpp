/*
 * FireButton.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/FireButton.h>

using namespace ndk_game;

FireButton::FireButton(android_app * app, int sw, int sh, BattleShip::Ptr bs): _bs(bs), _fadeOut(0)
{
    float w = sw * 0.18f,
            x = sw/2 - w/2,
            y = sh/2 - w/2;

    auto m = _norm->getModelMatrix();
    m = glm::translate(m, glm::vec3(x, y, 0.f));

    Log() << "fire button translate " << x << " x " << y;

    _norm = std::make_shared<Sprite>(
            Texture::create(std::make_shared<AssetTextureLoader>(app, "images/fire.png")),
            std::make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );
    _norm->getModelMatrix() = m;

    _pushed = std::make_shared<Sprite>(
            Texture::create(std::make_shared<AssetTextureLoader>(app, "images/fire_pushed.png")),
            std::make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );
    _pushed->getModelMatrix() = m;

    float xt = x - 2, yt = y - 2;
    _buttonRect = Rect(xt - w/2, yt - w/2, xt + w/2, yt + w/2);

#ifdef NDK_GAME_DEBUG
    _rect = std::make_shared<Sprite>(
            Texture::create(std::make_shared<AssetTextureLoader>(app, "images/white.png")),
            std::make_shared<RectSpriteLoader>(_buttonRect, 11, 0, 1, 0, 1)
            );
#endif

    _cur = _norm;
}

FireButton::~FireButton()
{
    Log() << "FireButton::~FireButton()";
}

void FireButton::update(double elapsed) throw (std::runtime_error)
{
    if (_fadeOut >= 0)
    {
        _fadeOut -= elapsed;
    }
    else if (_cur == _pushed) _cur = _norm;
}

void FireButton::input(int x, int y) throw (std::runtime_error)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _pushed;

        if (!_bs) throw std::runtime_error("battle ship is null");
        _bs->fire();

        _fadeOut = 0.1f;
    }
}

std::list<ndk_game::Sprite::Ptr> FireButton::getSprites() const throw ()
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}

std::string FireButton::getName() const throw ()
{
    return "FireButton";
}
