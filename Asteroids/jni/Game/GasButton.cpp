/*
 * GasButton.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/GasButton.h>

using namespace ndk_game;

GasButton::GasButton(android_app * app, int screenWidth, int screenHeight, BattleShip::Ptr bs)
{
    float w = screenWidth * 0.18f, x = -screenWidth/2 + w/2, y = screenHeight/2 - w/2;

    _norm = std::make_shared<Sprite>(
            Texture::create(std::make_shared<AssetTextureLoader>(app, "images/gas.png")),
            std::make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );
    _norm->getModelMatrix() = glm::translate(_norm->getModelMatrix(), glm::vec3(x, y, 0.f));

    _pushed = std::make_shared<Sprite>(
            Texture::create(std::make_shared<AssetTextureLoader>(app, "images/gas_pushed.png")),
            std::make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );
    _pushed->getModelMatrix() = glm::translate(_pushed->getModelMatrix(), glm::vec3(x, y, 0.f));

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

GasButton::~GasButton()
{
}

void GasButton::update(double elapsed) throw (std::runtime_error)
{
}

void GasButton::input(int x, int y) throw (std::runtime_error)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _pushed;

        if (!_bs) throw std::runtime_error("battle ship is null");
        _bs->gas();
    }
    else
    {
        _cur = _norm;
    }
}

std::list<ndk_game::Sprite::Ptr> GasButton::getSprites() const throw ()
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}
