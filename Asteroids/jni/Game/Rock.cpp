/*
 * Rock.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/Rock.h>
#include <Game/Bullet.h>
#include <Game/Explosion.h>

using namespace ndk_game;
using namespace glm;
using namespace std;

int Rock::rocks = 0;

std::list<Rock::Ptr> Rock::createRock(android_app* app,
        int screenWidth,
        int screenHeight,
        std::weak_ptr<ndk_game::IDrawEngine> engine,
        std::weak_ptr<ndk_game::Scene> winScene,
        std::weak_ptr<ndk_game::Scene> main,
        glm::vec3 pos,
        bool second)
{
    std::list<Rock::Ptr> rocks_;
    if (second)
    {
        int n = 5 + 5 * (float(rand()) / RAND_MAX);

        while (--n)
        {
            rocks_.push_back(shared_ptr<Rock>(new Rock(
                    app, screenWidth, screenHeight, engine, winScene, main, pos, second)));
        }
    }
    else
    {
        rocks_.push_back(shared_ptr<Rock>(new Rock(
                app, screenWidth, screenHeight, engine, winScene, main, pos, second)));
    }
    return rocks_;
}

ndk_game::Texture::Ptr Rock::loadTexture(android_app* app)
{
    static auto t = Texture::create(make_shared<AssetTextureLoader>(app, "images/rocks.png"));
    return t;
}

ndk_game::Texture::Ptr Rock::loadTextureRect(android_app* app)
{
    static auto tr = Texture::create(make_shared<AssetTextureLoader>(app, "images/white.png"));
    return tr;
}

Rock::Rock(android_app * app, int sw, int sh,
        weak_ptr<IDrawEngine> engine,
        weak_ptr<Scene> win,
        weak_ptr<Scene> main,
        glm::vec3 pos,
        bool second):
                _app(app), _second(second),
        _angle(0), _screenWidth(sw), _screenHeight(sh), _crash(false),
        _engine(engine), _winScene(win), _main(main)
{

    rocks++;

    Log() << "rocks " << rocks;

    enum{
        MIN_PARTS = 5, PARTS = 5
    };

    int l = MIN_PARTS + PARTS * (float(rand()) / RAND_MAX);
    float *rV = new float[(l + 2) * 5];

    float * p = rV;
    p[0] = 0;
    p[1] = 0;
    p[2] = 3.f;
    p[3] = .5f;
    p[4] = .5f;

    p += 5;

    float r0 = 0, rd = 2*M_PI / l, t0 = sw * 0.05f, tl = sw * 0.02f;
    if(_second){
        t0 = sw * 0.015f;
        tl = sw * 0.01f;
    }

    for (int i = 0; i < l + 1; ++i, r0 += rd, p+= 5) {

        float t = t0 + tl*float(rand())/RAND_MAX;
        p[0] = t*cos(r0);
        p[1] = t*sin(r0);

        p[2] = 3.f;

        p[3] = .5f + .45f * cos(r0);
        p[4] = .5f + .45f * sin(r0);
    }

    _rock = make_shared<Sprite>(
            loadTexture(app),
            make_shared<SimpleSpriteLoader>(rV, l + 2, ISpriteLoader::SpriteType::TriangleFan)
            );

    if (_second)
    {
        _pos = pos;

        float vel = 70.f + 100.f * (float(rand())/RAND_MAX),
                _angle = 2*M_PI / (float(rand())/RAND_MAX);

        _vel = vec3(vel * cos(_angle), vel * sin(_angle), 0.f);
    }
    else
    {
        _pos = vec3(-sw / 2 + sw * (float(rand()) / RAND_MAX),
                -sh / 2 + sh * (float(rand()) / RAND_MAX), 0.f);
        float vel = 30.f + 100.f * (float(rand())/RAND_MAX),
                _angle = 2*M_PI / (float(rand())/RAND_MAX);

        _vel = vec3(vel * cos(_angle), vel * sin(_angle), 0.f);
    }

    _rock->getModelMatrix() = translate(mat4(), _pos);

    _rockRect = Rect(-t0, -t0, t0, t0);

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(
            loadTextureRect(app),
            make_shared<RectSpriteLoader>(_rockRect, 11, 0, 1, 0, 1));
#endif
}

Rock::~Rock()
{
    Log() << "Rock::~Rock()";
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

void Rock::collision(IGameObject::Ptr obj) throw (runtime_error)
{
    if(obj->getName() != "Bullet")
        return;

    if((_rockRect + _pos) || dynamic_cast<Bullet*>(obj.get())->getRect()){

        if (!--rocks) if (auto e = _engine.lock()) e->setCurrentScene(
                _winScene.lock());

        Log() << "I am crash " << rocks;

//        if (auto s = _main.lock()) s->gameObject.push_back(
//                make_shared<Explosion>(_app, _screenWidth, _screenHeight, _pos.x, _pos.y));
        if (!_second){
            auto ls = createRock(_app, _screenWidth, _screenHeight, _engine, _winScene, _main, _pos, true);
            for (auto sp : ls)
                if (auto s = _main.lock()) s->gameObject.push_back(sp);
        }

        _crash = true;
    }
}

bool Rock::removeMe() const throw ()
{
    return _crash;
}

Rect Rock::getRect() const
{
    return (_rockRect + _pos);
}
