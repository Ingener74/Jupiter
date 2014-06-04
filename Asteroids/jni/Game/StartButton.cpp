/*
 * StartButton.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/StartButton.h>
#include <Game/Game.h>

using namespace ndk_game;
using namespace std;
using namespace glm;

StartButton::StartButton(int w, int h) :
        _fadeOut(0)
{
    float startButtonW = w * 0.6, startButtonH = h * 0.2;

    auto game = Game::instance();

    _sb1 = make_shared<Sprite>(
            game->getTexture("images/start.png"),
            make_shared<RectSpriteLoader>(startButtonW, startButtonH, 1, 0, 0.91, 0.95, 0.65)
            );

    _sb2 = make_shared<Sprite>(
            game->getTexture("images/start_pushed.png"),
            make_shared<RectSpriteLoader>(startButtonW, startButtonH, 1, 0, 0.91, 0.95, 0.65)
            );

    vec3 v(0.f, h * 0.2f, 0.f);
    auto m = translate(mat4(), v);

    _sb1->getModelMatrix() = m;
    _sb2->getModelMatrix() = m;

    _buttonRect = Rect(-startButtonW / 2, -startButtonH / 2, startButtonW / 2,
            startButtonH / 2) + v;

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(
            game->getTexture("images/white.png"),
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

        auto game = Game::instance();

        game->getEngine()->setCurrentScene(game->getScene("Main"));

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
