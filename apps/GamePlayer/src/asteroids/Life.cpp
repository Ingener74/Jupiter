/*
 * Life.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: ingener
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Life.h>

using namespace jupiter;
using namespace glm;
using namespace std;

Life::Life(int sw, int sh, GameTools tools): _tools(tools)
{
    _w = sw * 0.1f;
    _x = 0 /*sw/2 - w/2*/;
    _y = sh / 2 - _w / 2;

    newLife();
}

Life::~Life()
{
}

void Life::update(double elapsed)
{
}

std::list<std::shared_ptr<Sprite>> Life::getSprites() const
{
    return {_life};
}

std::string Life::getName() const
{
    return "Life";
}

void Life::setLife(int int1)
{
    cout << "set life = " << int1 << endl;

    _l = int1;
    newLife();
}

void Life::newLife()
{
//    auto game = Game::instance();

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

    auto lifeTexLoader = std::make_shared<jupiter::FileTextureLoader>("resources/" + lifeTex);

    auto lifeTexture = jupiter::Texture::create(lifeTexLoader);

    _life = std::make_shared<Sprite>(
            lifeTexture,
            std::make_shared<RectSpriteLoader>(_w, _w, 10, 0, 1, 1, 0)
            );

    _life->setModelMatrix(translate(mat4(), vec3(_x, _y, 0.f)));
}
