/*
 * BattleShip.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <BattleShip.h>
#include <Bullet.h>
#include <Rock.h>

using namespace glm;
using namespace std;
using namespace jupiter;

#define EPS 0.00001f

BattleShip::BattleShip(int screenWidth, int screenHeight,
        Life::Ptr life,
        std::shared_ptr<ISoundEngine> se,
        GameTools tools):
        _screenWidth(screenWidth), _screenHeight(screenHeight),
        _soundEngine(se),
        _lifeObj(life),
        _tools(tools)
{
    float shipSize = screenWidth * 0.1f;

    auto shipTexLoader = std::make_shared<jupiter::FileTextureLoader>("resources/images/ship.png");

    auto shipTexture = jupiter::Texture::create(shipTexLoader);

//    auto game = Game::instance();
//    auto t = game->getTexture("images/ship.png");

    _ship = make_shared<Sprite>(shipTexture, make_shared<RectSpriteLoader>(shipSize, shipSize, 2, 0, 0.5, 0, 0.5));
    _engineFire = make_shared<Sprite>(shipTexture, make_shared<RectSpriteLoader>(shipSize, shipSize, 3, 0.5, 1.0, 0, 0.5));

    float rs = shipSize*.7f/2;
    _shipRect = Rect(-rs/2, -rs/2, rs/2, rs/2);

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(
            game->getTexture("images/white.png"),
            make_shared<RectSpriteLoader>(_shipRect, 11, 0, 1, 0, 1)
            );
#endif
}

BattleShip::~BattleShip()
{
    cout << "BattleShip::~BattleShip()" << endl;
}

void BattleShip::update(double elapsed)
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

    _ship->setModelMatrix(m);
    _engineFire->setModelMatrix(m);
}

list<shared_ptr<Sprite>> BattleShip::getSprites() const
{
#ifdef NDK_GAME_DEBUG
    if (_gas) return {_ship, _rect, _engineFire};
    else return {_ship, _rect};
#else
    if (_gas) return {_ship, _engineFire};
    else return {_ship};
#endif
}

void BattleShip::fire()
{
    if (_armed < EPS)
    {
//        auto game = Game::instance();

        _tools.getScene("Main")->gameObject.push_front(make_shared<Bullet>(
                _screenWidth, _screenHeight, _pos.x, _pos.y, _angle));

//        game->getScene("Main")->gameObject.push_front(
//                make_shared<Bullet>(
//                        _screenWidth, _screenHeight, _pos.x, _pos.y, _angle));
        _armed = .5f;

        _soundEngine->loadSound("sounds/shot.mp3")->play();
    }
}

void BattleShip::right()
{
    _angle -= 0.07f;
}

void BattleShip::left()
{
    _angle += 0.07f;
}

string BattleShip::getName() const
{
    return "BattleShip";
}

void BattleShip::collision(shared_ptr<IGameObject> o)
{
    if (o->getName() != "Rock") return;

    Rect r = _shipRect + _pos;
    if (r || dynamic_cast<Rock*>(o.get())->getRect())
    {
//        auto game = Game::instance();

        if (_shield < EPS)
        {
            if (--_life <= 0)
            {
                cout << "Battle ship fail" << endl;
                _tools.setScene(_tools.getScene("Fail"));
//                game->getEngine()->setCurrentScene(game->getScene("Fail"));
            }
            _lifeObj->setLife(_life);
        }
        _shield = 3.f;

//        Log() << "shield " << _shield << " life " << _life;
    }
}

void BattleShip::gas()
{
    float f = 2000.f;
    _theForce = _theForce + vec3(f * sin(_angle), -f * cos(_angle), 0.f);

    _gas = true;
}
