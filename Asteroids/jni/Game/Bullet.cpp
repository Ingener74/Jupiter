/*
 * Bullet.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#include <Game/Bullet.h>

using namespace ndk_game;
using namespace glm;
using namespace std;

Bullet::Bullet(android_app * app, int sw, int sh, float x, float y, float angle):
        _angle(angle), _screenWidth(sw), _screenHeight(sh)
{
    auto v = 500.f;
    _vel = vec3(v * sin(angle), -v * cos(angle), 0.f);
    _pos = vec3(x, y, 0.f);

    float bsw = sw * 0.01f, bsh = sw * 0.02f;

    _bullet = make_shared<Sprite>(loadTexture(app), createSprite(bsw, bsh));

    float rs = bsw;
    _bulletRect = Rect(-rs/2, -rs/2, rs/2, rs/2);

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(loadTextureRect(app), createSpriteRect(_bulletRect));
#endif

}

Bullet::~Bullet()
{
    Log() << "Bullet::~Bullet()";
}

Texture::Ptr Bullet::loadTexture(android_app * app)
{
    static auto t = Texture::create(make_shared<AssetTextureLoader>(app, "images/bullet.png"));
    return t;
}

ISpriteLoader::Ptr Bullet::createSprite(int w, int h)
{
    static auto s = make_shared<RectSpriteLoader>(w, h, 6, 0, 66.f/128.f, 0, 1);
    return s;
}

#ifdef NDK_GAME_DEBUG
Texture::Ptr Bullet::loadTextureRect(android_app* app)
{
    static auto t = Texture::create(make_shared<AssetTextureLoader>(app, "images/white.png"));
    return t;
}

ISpriteLoader::Ptr Bullet::createSpriteRect(const Rect& r)
{
    static auto s = make_shared<RectSpriteLoader>(r, 11, 0, 1, 0, 1);
    return s;
}
#endif

void Bullet::update(double elapsed) throw (runtime_error)
{
    _pos = _pos + _vel * float(elapsed);

    auto m = translate(mat4(), _pos);

#ifdef NDK_GAME_DEBUG
    _rect->getModelMatrix() = m; // rect not rotating
#endif

    m = rotate(m, _angle, vec3(0.f, 0.f, 1.f));

    _bullet->getModelMatrix() = m;

}

list<ndk_game::Sprite::Ptr> Bullet::getSprites() const throw ()
{
#ifdef NDK_GAME_DEBUG
    return {_bullet, _rect};
#else
    return {_bullet};
#endif
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
    return false;
}
