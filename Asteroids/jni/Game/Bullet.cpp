/*
 * Bullet.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#include <Game/Bullet.h>
#include <Game/Rock.h>

using namespace ndk_game;
using namespace glm;
using namespace std;

Bullet::Bullet(android_app * app, int sw, int sh, float x, float y, float angle, Texture::Ptr bulletTex):
        _angle(angle), _screenWidth(sw), _screenHeight(sh), _remove(false)
{
    auto v = 500.f;
    _vel = vec3(v * sin(angle), -v * cos(angle), 0.f);
    _pos = vec3(x, y, 0.f);

    float bsw = sw * 0.01f, bsh = sw * 0.02f;

    _bullet = make_shared<Sprite>(
            bulletTex,
            make_shared<RectSpriteLoader>(bsw, bsh, 6, 0, 66.f / 128.f, 0, 1));

    float rs = bsw;
    _bulletRect = Rect(-rs/2, -rs/2, rs/2, rs/2);
}

Bullet::~Bullet()
{
    Log() << "Bullet::~Bullet()";
}

void Bullet::update(double elapsed) throw (runtime_error)
{
    _pos = _pos + _vel * float(elapsed);

    auto m = translate(mat4(), _pos);

    m = rotate(m, _angle, vec3(0.f, 0.f, 1.f));

    _bullet->getModelMatrix() = m;

}

list<ndk_game::Sprite::Ptr> Bullet::getSprites() const throw ()
{
    return {_bullet};
}


string Bullet::getName() const throw ()
{
    return "Bullet";
}

ndk_game::Rect Bullet::getRect() const throw ()
{
    return (_bulletRect + _pos);
}

bool Bullet::removeMe() const throw ()
{
    if (_pos.x >= _screenWidth / 2) return true;
    if (_pos.x <= -_screenWidth / 2) return true;
    if (_pos.y >= _screenHeight / 2) return true;
    if (_pos.y <= -_screenHeight / 2) return true;
    if (_remove) return true;
    return false;
}

void Bullet::collision(IGameObject::Ptr obj) throw (std::runtime_error)
{
    if (!obj) throw std::runtime_error("bullet collision object is null");

    if (obj->getName() != "Rock") return;

    auto r = _bulletRect + _pos;

    if (r || dynamic_cast<Rock*>(obj.get())->getRect()) _remove = true;
}
