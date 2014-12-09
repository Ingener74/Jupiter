/*
 * GasButton.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/GasButton.h>
#include <Game/Game.h>

using namespace ndk_game;

GasButton::GasButton(int screenWidth, int screenHeight, BattleShip::Ptr bs): _bs(bs), _fadeOut(0)
{
    float w = screenWidth * 0.18f, x = -screenWidth/2 + w/2, y = screenHeight/2 - w/2;

    auto game = Game::instance();

    _norm = std::make_shared<Sprite>(
            game->getTexture("images/gas.png"),
            std::make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );
    _norm->getModelMatrix() = glm::translate(_norm->getModelMatrix(), glm::vec3(x, y, 0.f));

    _pushed = std::make_shared<Sprite>(
            game->getTexture("images/gas_pushed.png"),
            std::make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );
    _pushed->getModelMatrix() = glm::translate(_pushed->getModelMatrix(), glm::vec3(x, y, 0.f));

    float xt = x - 2, yt = y - 2;
    _buttonRect = Rect(xt - w/2, yt - w/2, xt + w/2, yt + w/2);

#ifdef NDK_GAME_DEBUG
    _rect = std::make_shared<Sprite>(
            game->getTexture("images/white.png"),
            std::make_shared<RectSpriteLoader>(_buttonRect, 11, 0, 1, 0, 1)
            );
#endif

    _cur = _norm;
}

GasButton::~GasButton()
{
    Log() << "GasButton::~GasButton()";
}

void GasButton::update(double elapsed) throw (std::runtime_error)
{
    if (_fadeOut >= 0)
    {
        _fadeOut -= elapsed;
    }
    else if (_cur == _pushed) _cur = _norm;
}

void GasButton::input(int x, int y) throw (std::runtime_error)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _pushed;

        if (!_bs) throw std::runtime_error("battle ship is null");
        _bs->gas();

        _fadeOut = 0.1f;
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

std::string GasButton::getName() const throw ()
{
    return "GasButton";
}
