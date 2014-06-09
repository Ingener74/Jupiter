/*
 * Rock.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/Rock.h>
#include <Game/Bullet.h>
#include <Game/Explosion.h>
#include <Game/Game.h>

using namespace ndk_game;
using namespace glm;
using namespace std;

int Rock::rocks = 0;

std::list<Rock::Ptr> Rock::createRock(int screenWidth,
        int screenHeight,
        std::shared_ptr<ndk_game::ISoundEngine> soundEngine,
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
                    screenWidth, screenHeight, soundEngine, pos, second)));
        }
    }
    else
    {
        rocks_.push_back(shared_ptr<Rock>(new Rock(
                screenWidth, screenHeight, soundEngine, pos, second)));
    }
    return rocks_;
}

Rock::Rock(int sw, int sh,
        std::shared_ptr<ndk_game::ISoundEngine> soundEngine,
        glm::vec3 pos,
        bool second):_second(second), _screenWidth(sw),
                _screenHeight(sh), _soundEngine(soundEngine)
{

    rocks++;

    enum{
        MIN_PARTS = 5, PARTS = 5
    };

    int l = MIN_PARTS + PARTS * (float(rand()) / RAND_MAX);
    float *rV = new float[(l + 2) * 5];

    float * p = rV;
    p[0] = 0;
    p[1] = 0;
    p[2] = 4.f;
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

        p[2] = 4.f;

        p[3] = .5f + .45f * cos(r0);
        p[4] = .5f + .45f * sin(r0);
    }

    _rock = make_shared<Sprite>(
            Game::instance()->getTexture("images/rocks1.png"),
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

    m = rotate(m, _angle, vec3(0.f, 0.f, 1.f));

    _rock->getModelMatrix() = m;
}

list<Sprite::Ptr> Rock::getSprites() const throw ()
{
    return {_rock};
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

        auto game = Game::instance();

        if (!--rocks)
            game->getEngine()->setCurrentScene(game->getScene("Win"));

        Log() << "I am crash " << rocks;

        _soundEngine->loadSound("sounds/explosion.mp3")->play();

        if (!_second){
            auto ls = createRock(_screenWidth, _screenHeight, _soundEngine, _pos, true);
            for (auto sp : ls)
                game->getScene("Main")->gameObject.push_front(sp);
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

void Rock::reset()
{
    rocks = 0;
}
