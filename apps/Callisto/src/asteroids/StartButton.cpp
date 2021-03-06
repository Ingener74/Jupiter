/*
 * StartButton.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <StartButton.h>

using namespace jupiter;
using namespace std;
using namespace glm;

StartButton::StartButton(int w, int h, GameTools tools) :
        _fadeOut(0), _tools(tools)
{
    float startButtonW = w * 0.6, startButtonH = h * 0.2;

//    Image im{"resources/images/start.png"};
//    Sprite s{Texture{im}, im};

    _sb1 = make_shared<Sprite>(Texture::create(make_shared<FileTextureLoader>("resources/images/start.png")),
            make_shared<RectSpriteLoader>(startButtonW, startButtonH, 1, 0, 0.91, 0.95, 0.65));

    _sb2 = make_shared<Sprite>(Texture::create(make_shared<FileTextureLoader>("resources/images/start_pushed.png")),
            make_shared<RectSpriteLoader>(startButtonW, startButtonH, 1, 0, 0.91, 0.95, 0.65));

//    auto m = translate(mat4{}, vec3 v{0.f, h * 0.2f, 0.f});

//    _sb1->setModelMatrix(m);
//    _sb2->setModelMatrix(m);

    _buttonRect = Rect(-startButtonW / 2, -startButtonH / 2, startButtonW / 2,
            startButtonH / 2)/* + v*/;

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
    cout << "StartButton::~StartButton()" << endl;
}

void StartButton::update(double elapsed)
{
    if (_fadeOut >= 0)
    {
        _fadeOut -= elapsed;
    }
    else if (_cur == _sb2) _cur = _sb1;
}
void StartButton::input(int x, int y)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _sb2;

        _tools.setScene(_tools.getScene("Main"));

        _fadeOut = 0.1f;
    }
}
list<shared_ptr<Sprite>> StartButton::getSprites() const
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}

string StartButton::getName() const
{
    return "StartButton";
}
