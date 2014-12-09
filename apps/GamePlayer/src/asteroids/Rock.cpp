/*
 * Rock.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Rock.h>
#include <Bullet.h>
//#include <Explosion.h>

using namespace jupiter;
using namespace glm;
using namespace std;

int Rock::rocks = 0;

list<Rock::Ptr> Rock::createRock(int screenWidth, int screenHeight,
        shared_ptr<ISoundEngine> soundEngine,
        glm::vec3 pos,
        GameTools tools,
        bool second)
{
    list<Rock::Ptr> rocks_;
    if (second)
    {
        int n = 5 + 5 * (float(rand()) / RAND_MAX);

        while (--n)
        {
            rocks_.push_back(shared_ptr<Rock>(new Rock(screenWidth, screenHeight, soundEngine, pos, tools, second)));
        }
    }
    else
    {
        rocks_.push_back(shared_ptr<Rock>(new Rock(screenWidth, screenHeight, soundEngine, pos, tools, second)));
    }
    return rocks_;
}

Rock::Rock(int sw, int sh,
        shared_ptr<ISoundEngine> soundEngine,
        glm::vec3 pos,
        GameTools tools,
        bool second):
                _second(second),
                _screenWidth(sw),
                _screenHeight(sh),
                _soundEngine(soundEngine),
                _tools(tools)
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

    auto rockTexLoader = make_shared<jupiter::FileTextureLoader>(
            _tools.gameLocation() + "/resources/images/rocks1.png");

    auto rockTexture = jupiter::Texture::create(rockTexLoader);

    _rock = make_shared<Sprite>(
            rockTexture,
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

    _rock->setModelMatrix(translate(mat4(), _pos));

    _rockRect = Rect(-t0, -t0, t0, t0);

}

Rock::~Rock()
{
    cout << "Rock::~Rock()" << endl;
}

void Rock::update(double elapsed)
{
    _pos = _pos + _vel * float(elapsed);

    if (_pos.x >= _screenWidth / 2) _pos.x -= _screenWidth;
    if (_pos.x <= - _screenWidth / 2) _pos.x += _screenWidth;
    if (_pos.y >= _screenHeight / 2) _pos.y -= _screenHeight;
    if (_pos.y <= - _screenHeight / 2) _pos.y += _screenHeight;

    auto m = translate(mat4(), _pos);

    m = rotate(m, _angle, vec3(0.f, 0.f, 1.f));

    _rock->setModelMatrix(m);
}

list<shared_ptr<Sprite>> Rock::getSprites() const
{
    return {_rock};
}

string Rock::getName() const
{
    return "Rock";
}

void Rock::collision(shared_ptr<IGameObject> obj)
{
    if(obj->getName() != "Bullet")
        return;

    if((_rockRect + _pos) || dynamic_cast<Bullet*>(obj.get())->getRect()){

//        auto game = Game::instance();

        if (!--rocks)
            _tools.setScene(_tools.getScene("Win"));
//            game->getEngine()->setCurrentScene(game->getScene("Win"));

        cout << "I am crash " << rocks << endl;

        _soundEngine->loadSound("sounds/explosion.mp3")->play();

        if (!_second){
            auto ls = createRock(_screenWidth, _screenHeight, _soundEngine, _pos, _tools, true);
            for (auto sp : ls)
                _tools.setScene(_tools.getScene("Main"));
//                game->getScene("Main")->gameObject.push_front(sp);
        }

        _crash = true;
    }
}

bool Rock::removeMe() const
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
