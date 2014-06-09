/*
 * Life.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: ingener
 */

#include <Game/Life.h>
#include <Game/Game.h>

using namespace ndk_game;
using namespace glm;
using namespace std;

Life::Life(int sw, int sh)
{
    _w = sw * 0.1f;
    _x = 0 /*sw/2 - w/2*/;
    _y = sh / 2 - _w / 2;

    newLife();
}

Life::~Life()
{
}

void Life::update(double elapsed) throw (std::runtime_error)
{
}

std::list<ndk_game::Sprite::Ptr> Life::getSprites() const throw ()
{
    return {_life};
}

std::string Life::getName() const throw ()
{
    return "Life";
}

void Life::setLife(int int1)
{
    Log() << "set life = " << int1;

    _l = int1;
    newLife();
}

void Life::newLife()
{
    auto game = Game::instance();

    string lifeTex;
    switch (_l)
    {
        case 1:
            lifeTex = "images/life/life1.png";
            break;
        case 2:
            lifeTex = "images/life/life2.png";
            break;
        case 3:
            lifeTex = "images/life/life3.png";
            break;
        default:
            lifeTex = "images/life/life3.png";
    }

    Log() << "new life = " << lifeTex;

    _life = std::make_shared<Sprite>(
            game->getTexture(lifeTex),
            std::make_shared<RectSpriteLoader>(_w, _w, 10, 0, 1, 1, 0)
            );

    _life->getModelMatrix() = translate(mat4(), vec3(_x, _y, 0.f));
}
