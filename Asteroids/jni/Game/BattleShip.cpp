/*
 * BattleShip.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/BattleShip.h>
#include <Game/Bullet.h>
#include <Game/Rock.h>

using namespace ndk_game;
using namespace glm;
using namespace std;

#define EPS 0.00001f

BattleShip::BattleShip(android_app * app, int screenWidth, int screenHeight,
        std::weak_ptr<ndk_game::Scene> parent,
        std::weak_ptr<ndk_game::Scene> fail,
        std::weak_ptr<ndk_game::IDrawEngine> e):

        _app(app), _gas(false), _mass(10.f), _angle(0),
        _screenWidth(screenWidth), _screenHeight(screenHeight),
        _parentScene(parent), _failScene(fail), _engine(e), _armed(0), _life(3), _shield(0)
{
    float shipSize = screenWidth * 0.1f;

    auto t = Texture::create(make_shared<AssetTextureLoader>(app, "images/ship.png"));
    _ship = make_shared<Sprite>(t,
            make_shared<RectSpriteLoader>(shipSize, shipSize, 2, 0, 0.5, 0, 0.5)
            );

    _engineFire = make_shared<Sprite>(t,
            make_shared<RectSpriteLoader>(shipSize, shipSize, 3, 0.5, 1.0, 0, 0.5)
            );

    float rs = shipSize*.7f/2;
    _shipRect = Rect(-rs/2, -rs/2, rs/2, rs/2);

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/white.png")),
            make_shared<RectSpriteLoader>(_shipRect, 11, 0, 1, 0, 1)
            );
#endif

}

BattleShip::~BattleShip()
{
    Log() << "BattleShip::~BattleShip()";
}

void BattleShip::update(double elapsed) throw (runtime_error)
{
    if (_armed > EPS)
    {
        _armed -= elapsed;
    }
    if (_shield > EPS)
    {
        _shield -= elapsed;
    }

    _theForce = vec3(_theForce.x * .5f, _theForce.y * .5f, 0.f);

    if (abs(_theForce.x) < .05f && abs(_theForce.y) < .05f) _gas =
            false;

    vec3 forces = _theForce;

    _acc = forces * (1 / _mass);
    _vel = _vel + _acc * float(elapsed);
    _pos = _pos + _vel * float(elapsed);

    if (_pos.x >= _screenWidth / 2) _pos.x -= _screenWidth;
    if (_pos.x <= - _screenWidth / 2) _pos.x += _screenWidth;
    if (_pos.y >= _screenHeight / 2) _pos.y -= _screenHeight;
    if (_pos.y <= - _screenHeight / 2) _pos.y += _screenHeight;

    auto m = translate(mat4(), _pos);

#ifdef NDK_GAME_DEBUG
    _rect->getModelMatrix() = m; // rect not rotating
#endif

    m = rotate(m, _angle, vec3(0.f, 0.f, 1.f));

    _ship->getModelMatrix() = m;
    _engineFire->getModelMatrix() = m;
}

list<Sprite::Ptr> BattleShip::getSprites() const throw ()
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
    if (_armed < EPS)
    {
        if (auto p = _parentScene.lock()) p->gameObject.push_back(
                make_shared<Bullet>(_app, _screenWidth, _screenHeight, _pos.x,
                        _pos.y, _angle));
        _armed = .5f;
    }
}

void BattleShip::right() throw ()
{
    _angle -= 0.05f;
}

void BattleShip::left() throw ()
{
    _angle += 0.05f;
}

string BattleShip::getName() const throw ()
{
    return "BattleShip";
}

void BattleShip::collision(IGameObject::Ptr o) throw (std::runtime_error)
{
    if (o->getName() != "Rock") return;

    if((_shipRect + _pos) || dynamic_cast<Rock*>(o.get())->getRect()){

        Log() << "battle ship collision " << (_shipRect + _pos) << "  ===  " << dynamic_cast<Rock*>(o.get())->getRect();

        if (_shield > EPS) if (--_life) if (auto eng = _engine.lock())
        {
            Log() << "Battle ship fail";

            eng->setCurrentScene(_failScene.lock());
            _shield = 3.f;
        }
    }
}

void BattleShip::gas() throw ()
{
    float f = 2000.f;
    _theForce = _theForce + vec3(f * sin(_angle), -f * cos(_angle), 0.f);

    _gas = true;
}
