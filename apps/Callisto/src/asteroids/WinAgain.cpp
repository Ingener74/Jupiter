/*
 * WinAgain.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <WinAgain.h>
#include <Rock.h>

using namespace jupiter;
using namespace std;
using namespace glm;

WinAgain::WinAgain(int screenWidth, GameTools tools, std::function<void()> newGame): _newGame(newGame), _tools(tools)
{
    float winButtonW = screenWidth * 0.8, winButtonH = screenWidth * 0.4;

    _norm = make_shared<Sprite>(
            Texture::create(make_shared<FileTextureLoader>("resources/images/win_again.png")),
            make_shared<RectSpriteLoader>(winButtonW, winButtonH, 1, 0.05, 0.95, 0.95, 0.52)
            );

    _pushed = make_shared<Sprite>(
            Texture::create(make_shared<FileTextureLoader>("resources/images/win_again_pushed.png")),
            make_shared<RectSpriteLoader>(winButtonW, winButtonH, 1, 0.05, 0.95, 0.95, 0.52)
            );

    _pushed->setModelMatrix(translate(_pushed->getModelMatrix(), vec3{2.f, -2.f, 0.f}));

    _buttonRect = Rect(-winButtonW / 2, -winButtonH / 2, winButtonW / 2,
            winButtonH / 2);

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/white.png")),
            make_shared<RectSpriteLoader>(_buttonRect, 2, 0, 0.91, 1, 0.4)
            );
#endif

    _cur = _norm;
}

WinAgain::~WinAgain()
{
    cout << "WinAgain::~WinAgain()" << endl;
}

void WinAgain::update(double elapsed)
{
    if (_fadeOut >= 0)
    {
        _fadeOut -= elapsed;
    }
    else if (_cur == _pushed) _cur = _norm;
}

void WinAgain::input(int x, int y)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _pushed;

        Rock::reset();

        _newGame();
        _tools.setScene(_tools.getScene("Main"));

//        game->newGame();
//        game->getEngine()->setCurrentScene(game->getScene("Main"));

        _fadeOut = 0.1f;
    }
}

list<shared_ptr<Sprite>> WinAgain::getSprites() const
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}

string WinAgain::getName() const
{
    return "YouWinAndTryAgain";
}
