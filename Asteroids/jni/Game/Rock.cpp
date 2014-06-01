/*
 * Rock.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/Rock.h>
#include <Game/Bullet.h>

using namespace ndk_game;
using namespace glm;
using namespace std;


Rock::Rock(android_app * app, int sw, int sh):
        _angle(0), _screenWidth(sw), _screenHeight(sh), _crash(false)
{
    enum{
        MIN_PARTS = 5, PARTS = 5
    };

    int l = MIN_PARTS + PARTS * (float(rand()) / RAND_MAX);
    float R = 100.3f, *rV = new float[(l + 2) * 5];

    float * p = rV;
    p[0] = 0;
    p[1] = 0;
    p[2] = 3.f;
    p[3] = .5f;
    p[4] = .5f;

    p += 5;

    float r0 = 0, rd = 2*M_PI / l, t0 = sw * 0.05f, tl = sw * 0.02f;

    for (int i = 0; i < l + 1; ++i, r0 += rd, p+= 5) {

        float t = t0 + tl*float(rand())/RAND_MAX;
        p[0] = t*cos(r0);
        p[1] = t*sin(r0);

        p[2] = 3.f;

        p[3] = .5f + .45f * cos(r0);
        p[4] = .5f + .45f * sin(r0);

//        Log() << i << " p0 " << setw(13) << p[0] << " p1 " << setw(13) << p[1] << " p2 " << setw(13) << p[2] << " p3 " << setw(13) << p[3] << " p4 " << setw(13) << p[4];
    }

    _rock = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/rocks.png")),
            make_shared<SimpleSpriteLoader>(rV, l + 2, ISpriteLoader::SpriteType::TriangleFan)
            );

    _pos = vec3(
            -sw/2 + sw * (float(rand())/RAND_MAX),
            -sh/2 + sh * (float(rand())/RAND_MAX), 0.f);

    float vel = 30.f + 100.f * (float(rand())/RAND_MAX),
            _angle = 2*M_PI / (float(rand())/RAND_MAX);

    _vel = vec3(vel * cos(_angle), vel * sin(_angle), 0.f);

    _rock->getModelMatrix() = translate(mat4(), _pos);

    _rockRect = Rect(-t0, -t0, t0, t0);

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/white.png")),
            make_shared<RectSpriteLoader>(_rockRect, 11, 0, 1, 0, 1));
#endif
}

Rock::~Rock()
{
}

void Rock::update(double elapsed) throw (runtime_error)
{
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

    _rock->getModelMatrix() = m;
}

list<Sprite::Ptr> Rock::getSprites() const throw ()
{
#ifdef NDK_GAME_DEBUG
    return {_rock, _rect};
#else
    return {_rock};
#endif
}

string Rock::getName() const throw ()
{
    return "Rock";
}

void Rock::collision(IGameObject::Ptr obj) throw (std::runtime_error)
{
    if(obj->getName() != "Bullet")
        return;

    if((_rockRect + _pos) || dynamic_cast<Bullet*>(obj.get())->getRect()){

        Log() << "I am crash";

        _crash = true;
    }
}

bool Rock::removeMe() const throw ()
{
    return _crash;
}

ndk_game::Rect Rock::getRect() const
{
    return (_rockRect + _pos);
}
