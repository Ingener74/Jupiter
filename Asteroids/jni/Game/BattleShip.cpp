/*
 * BattleShip.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/BattleShip.h>

using namespace ndk_game;

BattleShip::BattleShip(android_app * app, int screenWidth) :
        _gas(true)
{
    float shipSize = screenWidth * 0.1f;

    auto t = Texture::create(std::make_shared<AssetTextureLoader>(app, "images/ship.png"));
    _ship = std::make_shared<Sprite>(t,
            std::make_shared<RectSpriteLoader>(shipSize, shipSize, 2, 0, 0.5, 0, 0.5)
            );

    _engineFire = std::make_shared<Sprite>(t,
            std::make_shared<RectSpriteLoader>(shipSize, shipSize, 3, 0.5, 1.0, 0, 0.5)
            );
}

BattleShip::~BattleShip()
{
    Log() << "BattleShip::~BattleShip()";
}

void BattleShip::update(double elapsed) throw (std::runtime_error)
{
}

void BattleShip::input(int x, int y) throw (std::runtime_error)
{
}

std::list<Sprite::Ptr> BattleShip::getSprites() const throw ()
{
    if (_gas) return {_ship, _engineFire};
    else return {_ship};
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
}
