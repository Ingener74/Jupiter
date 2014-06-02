/*
 * Explosion.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#include <Game/Explosion.h>

using namespace ndk_game;
using namespace glm;
using namespace std;

#define EPS 0.00001

Explosion::Explosion(android_app* app, int screenWidth, int screenHeight, float x, float y):
                _x(x), _y(y), _currentSprite(0), _remove(false),
                _delta(1.f / 30.f)
{
    Log() << "Create explosion";

    _expSprites = createSprites(app, screenWidth, screenHeight);
    _curSprite = _expSprites.front();
    _curSprite->getModelMatrix() = translate(mat4(), vec3(_x, _y, 0.f));
}

Explosion::~Explosion()
{
    Log() << "Explosion::~Explosion()";
}

vector<Sprite::Ptr> Explosion::createSprites(android_app* app, int sw, int sh)
{
    int w = sw * 0.1f, h = (83.f / 63.f) * w;

    Log() << "explotion size " << w << " x " << h;

    static vector<Sprite::Ptr> sprites;
    if(sprites.empty()){
        for (int i = 0; i < 12; ++i)
        {
            stringstream ss;
            ss << "images/explosion/" << i + 1 << ".png";

            Log() << "Create explosion sprite " << (i + 1);

            sprites.push_back(
                make_shared<Sprite>(
                    Texture::create(make_shared<AssetTextureLoader>(app, ss.str())),
                    make_shared<RectSpriteLoader>(w, h, 6, 0, 1, 0, 1)
                )
            );
        }
    }
    return sprites;
}

void Explosion::update(double elapsed) throw (runtime_error)
{
//    if (_delta < EPS)
//    {
//        _delta = 1.f / 30.f;
//        if (++_currentSprite >= _expSprites.size())
//        {
//            Log() << "remove explosion";
//            _remove = true;
//        }
//        else
//        {
//            Log() << "set explosion sprite " << _currentSprite;
//
//            _curSprite = _expSprites[_currentSprite];
//            _curSprite->getModelMatrix() = translate(mat4(), vec3(_x, _y, 0.f));
//        }
//    }
//    _delta -= elapsed;

    if (++_currentSprite >= _expSprites.size())
    {
        Log() << "remove explosion";
        _remove = true;
    }
    else
    {
        Log() << "set explosion sprite " << _currentSprite;

        _curSprite = _expSprites[_currentSprite];
        _curSprite->getModelMatrix() = translate(mat4(), vec3(_x, _y, 0.f));
    }
}

string Explosion::getName() const throw ()
{
    return "Explosion";
}

list<Sprite::Ptr> Explosion::getSprites() const throw ()
{
    return {_curSprite};
}

bool Explosion::removeMe() const throw ()
{
    return _remove;
}
