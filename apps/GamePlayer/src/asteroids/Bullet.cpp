/*
 * Bullet.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Bullet.h>
#include <Rock.h>

using namespace jupiter;
using namespace glm;
using namespace std;

Bullet::Bullet(int sw, int sh, float x, float y, float angle):
        _angle(angle), _screenWidth(sw), _screenHeight(sh), _remove(false)
{
    auto v = 500.f;
    _vel = vec3(v * sin(angle), -v * cos(angle), 0.f);
    _pos = vec3(x, y, 0.f);

    float bsw = sw * 0.01f, bsh = sw * 0.02f;

//    auto game = Game::instance();

    auto bulletTexLoader = std::make_shared<jupiter::FileTextureLoader>("resources/images/bullet.png");

    auto bulletTexture = Texture::create(bulletTexLoader);

    _bullet = make_shared<Sprite>(
            bulletTexture,
            make_shared<RectSpriteLoader>(bsw, bsh, 6, 0, 66.f / 128.f, 0, 1));

    float rs = bsw;
    _bulletRect = Rect(-rs/2, -rs/2, rs/2, rs/2);
}

Bullet::~Bullet()
{
    cout << "Bullet::~Bullet()" << endl;
}

void Bullet::update(double elapsed)
{
    _pos = _pos + _vel * float(elapsed);

    auto m = translate(mat4(), _pos);

    m = rotate(m, _angle, vec3(0.f, 0.f, 1.f));

    _bullet->setModelMatrix(m);
}

list<shared_ptr<Sprite>> Bullet::getSprites() const
{
    return {_bullet};
}


string Bullet::getName() const
{
    return "Bullet";
}

Rect Bullet::getRect() const
{
    return (_bulletRect + _pos);
}

bool Bullet::removeMe() const
{
    if (_pos.x >= _screenWidth / 2) return true;
    if (_pos.x <= -_screenWidth / 2) return true;
    if (_pos.y >= _screenHeight / 2) return true;
    if (_pos.y <= -_screenHeight / 2) return true;
    if (_remove) return true;
    return false;
}

void Bullet::collision(shared_ptr<IGameObject> obj)
{
    if (!obj) throw JupiterError("bullet collision object is null");

    if (obj->getName() != "Rock") return;

    auto r = _bulletRect + _pos;

    if (r || dynamic_cast<Rock*>(obj.get())->getRect()) _remove = true;
}
