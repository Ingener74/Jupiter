/*
 * GasButton.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GasButton.h>

using namespace jupiter;
using namespace std;
using namespace glm;

GasButton::GasButton(int screenWidth, int screenHeight, BattleShip::Ptr bs): _bs(bs), _fadeOut(0)
{
    float w = screenWidth * 0.18f, x = -screenWidth/2 + w/2, y = screenHeight/2 - w/2;

    _norm = make_shared<Sprite>(
            Texture::create(make_shared<FileTextureLoader>("resources/images/gas.png")),
            make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );

    auto m = translate(_norm->getModelMatrix(), vec3{x, y, 0.f});
    _norm->setModelMatrix(m);

    _pushed = make_shared<Sprite>(
            Texture::create(make_shared<FileTextureLoader>("resources/images/gas_pushed.png")),
            make_shared<RectSpriteLoader>(w, w, 10, 0, 1, 1, 0)
            );
    _pushed->setModelMatrix(m);

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

GasButton::~GasButton()
{
    cout << "GasButton::~GasButton()" << endl;
}

void GasButton::update(double elapsed)
{
    if (_fadeOut >= 0)
    {
        _fadeOut -= elapsed;
    }
    else if (_cur == _pushed) _cur = _norm;
}

void GasButton::input(int x, int y)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _pushed;

        if (!_bs) throw runtime_error("battle ship is null");
        _bs->gas();

        _fadeOut = 0.1f;
    }
}

list<shared_ptr<Sprite>> GasButton::getSprites() const
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}

string GasButton::getName() const
{
    return "GasButton";
}
