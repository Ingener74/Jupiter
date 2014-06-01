/*
 * Rock.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/Rock.h>

using namespace ndk_game;
using namespace glm;
using namespace std;

enum{
    MAX_PARTS = 5
};

Rock::Rock(android_app * app, int sw, int sh):
        _angle(0), _screenWidth(sw), _screenHeight(sh)
{
    int l = 5 + MAX_PARTS * (float(rand()) / RAND_MAX);
    Log() << "Rock parts " << l;
    float R = 100.3f, *rV = new float[(l + 2) * 5];

    float x = 0, y = 0;

    float * p = rV;
    p[0] = x;
    p[1] = y;
    p[2] = 3.f;
    p[3] = .5f; //float(rand())/RAND_MAX;
    p[4] = .5f; //float(rand())/RAND_MAX;

    p += 5;

    float r0 = 0, rd = 2*M_PI / l, t0 = sw * 0.05f, tl = sw * 0.02f;

    Log() << "r0 = " << r0 << " rd = " << rd << " t0 = " << t0 << " tl = " << tl;

    for (int i = 0; i < l + 1; ++i, r0 += rd, p+= 5) {

        float t = t0 + tl*float(rand())/RAND_MAX;
        p[0] = x + t*cos(r0);
        p[1] = y + t*sin(r0);

        p[2] = 3.f;

        p[3] = .5f + 0.5f * cos(r0); // float(rand())/RAND_MAX;
        p[4] = .5f + 0.5f * sin(r0); // float(rand())/RAND_MAX;

        Log() << "p0 " << p[0] << " p1 " << p[1] << " p2 " << p[2] << " p3 " << p[3] << " p4 " << p[4];
    }

    _rock = make_shared<Sprite>(
            loadTexture(app),
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
    _rect = make_shared<Sprite>(loadTextureRect(app), createSpriteRect(_rockRect));
#endif
}

Rock::~Rock()
{
}

Texture::Ptr Rock::loadTexture(android_app* app)
{
    static auto rt = Texture::create(make_shared<AssetTextureLoader>(app, "images/rocks.png"));
    return rt;
}

Texture::Ptr Rock::loadTextureRect(android_app* app)
{
    static auto t = Texture::create(make_shared<AssetTextureLoader>(app, "images/white.png"));
    return t;
}

ISpriteLoader::Ptr Rock::createSpriteRect(const Rect& r)
{
    static auto s = make_shared<RectSpriteLoader>(r, 11, 0, 1, 0, 1);
    return s;
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

void Rock::input(int x, int y) throw (runtime_error)
{
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
