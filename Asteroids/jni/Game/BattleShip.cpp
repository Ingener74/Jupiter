/*
 * BattleShip.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/BattleShip.h>

using namespace ndk_game;

#define EPS 0.00001f

BattleShip::BattleShip(android_app * app, int screenWidth, int screenHeight) :
        _gas(false), _mass(10.f), _screenWidth(screenWidth), _screenHeight(screenHeight)
{
    float shipSize = screenWidth * 0.1f;

    auto t = Texture::create(std::make_shared<AssetTextureLoader>(app, "images/ship.png"));
    _ship = std::make_shared<Sprite>(t,
            std::make_shared<RectSpriteLoader>(shipSize, shipSize, 2, 0, 0.5, 0, 0.5)
            );

    _engineFire = std::make_shared<Sprite>(t,
            std::make_shared<RectSpriteLoader>(shipSize, shipSize, 3, 0.5, 1.0, 0, 0.5)
            );

    float rs = shipSize*.7f/2;
    _shipRect = Rect(-rs/2, -rs/2, rs/2, rs/2);

#ifdef NDK_GAME_DEBUG
    _rect = std::make_shared<Sprite>(
            Texture::create(std::make_shared<AssetTextureLoader>(app, "images/white.png")),
            std::make_shared<RectSpriteLoader>(_shipRect, 11, 0, 1, 0, 1)
            );
#endif

}

BattleShip::~BattleShip()
{
    Log() << "BattleShip::~BattleShip()";
}

void BattleShip::update(double elapsed) throw (std::runtime_error)
{
    _theForce = glm::vec3(_theForce.x * .5f, _theForce.y * .5f, 0.f);

    if (std::abs(_theForce.x) < .05f && std::abs(_theForce.y) < .05f) _gas =
            false;

    glm::vec3 forces = _theForce + resistance(_vel);

    _acc = forces * (1 / _mass);
    _vel = _vel + _acc * float(elapsed);
    _pos = _pos + _vel * float(elapsed);

    if (_pos.x >= _screenWidth / 2) _pos.x -= _screenWidth;
    if (_pos.x <= - _screenWidth / 2) _pos.x += _screenWidth;
    if (_pos.y >= _screenHeight / 2) _pos.y -= _screenHeight;
    if (_pos.y <= - _screenHeight / 2) _pos.y += _screenHeight;

    Log() << "battle ship position << " << _pos.x << " x " << _pos.y;

    glm::mat4 m = _ship->getModelMatrix();

    m = glm::translate(m, _pos);

    _ship->getModelMatrix() = m;
    _engineFire->getModelMatrix() = m;
#ifdef NDK_GAME_DEBUG
    _rect->getModelMatrix() = m;
#endif
}

void BattleShip::input(int x, int y) throw (std::runtime_error)
{
}

std::list<Sprite::Ptr> BattleShip::getSprites() const throw ()
{
#ifdef NDK_GAME_DEBUG
    if (_gas) return {_ship, _rect, _engineFire};
    else return {_ship, _rect};
#else
    if (_gas) return {_ship, _engineFire};
    else return {_ship};
#endif
}

void BattleShip::fire() throw ()
{
    Log() << "Battle ship FIRE";
}

void BattleShip::right() throw ()
{
    glm::mat4 m = _ship->getModelMatrix();

    m = glm::rotate(m, 0.1f, glm::vec3(0.f, 0.f, 1.f));

    _ship->getModelMatrix() = _engineFire->getModelMatrix() = m;
}

void BattleShip::left() throw ()
{
    glm::mat4 m = _ship->getModelMatrix();

    m = glm::rotate(m, -0.1f, glm::vec3(0.f, 0.f, 1.f));

    _ship->getModelMatrix() = _engineFire->getModelMatrix() = m;
}

std::string BattleShip::getName() const throw ()
{
    return "BattleShip";
}

void BattleShip::gas() throw ()
{
    float f = 50.f;
    _theForce = _theForce + glm::vec3(0.f, -f, 0.f);

    _gas = true;
}

glm::vec3 BattleShip::resistance(glm::vec3 velocity)
{
    const float resForce = 1000.f;
    return glm::vec3(
            (velocity.x > EPS) ? -(resForce*velocity.x*velocity.x) : (velocity.x < -EPS) ? (resForce*velocity.x*velocity.x) : 0.f,
            (velocity.y > EPS) ? -(resForce*velocity.y*velocity.y) : (velocity.y < -EPS) ? (resForce*velocity.y*velocity.y) : 0.f,
            0.f);
}
