/*
 * StartButton.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/StartButton.h>

using namespace ndk_game;
using namespace std;
using namespace glm;

StartButton::StartButton(android_app * app, int screenWidth, int screenHeight,
        weak_ptr<ndk_game::IDrawEngine> engine,
        weak_ptr<ndk_game::Scene> mainScene) :
        _engine(engine), _mainScene(mainScene), _fadeOut(0)
{
    float startButtonW = screenWidth * 0.6, startButtonH = screenWidth * 0.2;

    _sb1 = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/start.png")),
            make_shared<RectSpriteLoader>(startButtonW, startButtonH, 1, 0, 0.91, 0.95, 0.65)
            );

    _sb2 = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/start_pushed.png")),
            make_shared<RectSpriteLoader>(startButtonW, startButtonH, 1, 0, 0.91, 0.95, 0.65)
            );

    vec3 v(0.f, screenHeight * 0.2f, 0.f);
    auto m = translate(mat4(), v);

    _sb1->getModelMatrix() = m;
    _sb2->getModelMatrix() = m;

    _buttonRect = Rect(-startButtonW / 2, -startButtonH / 2, startButtonW / 2,
            startButtonH / 2) + v;

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/white.png")),
            make_shared<RectSpriteLoader>(_buttonRect, 2, 0, 0.91, 1, 0.4)
            );
#endif

    _cur = _sb1;
}

StartButton::~StartButton()
{
    Log() << "StartButton::~StartButton()";
}

void StartButton::update(double elapsed) throw (runtime_error)
{
    if (_fadeOut >= 0)
    {
        _fadeOut -= elapsed;
    }
    else if (_cur == _sb2) _cur = _sb1;
}
void StartButton::input(int x, int y) throw (runtime_error)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _sb2;

        if(auto e = _engine.lock())e->setCurrentScene(_mainScene.lock());

        _fadeOut = 0.1f;
    }
}
list<Sprite::Ptr> StartButton::getSprites() const throw ()
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}

string StartButton::getName() const throw ()
{
    return "StartButton";
}
