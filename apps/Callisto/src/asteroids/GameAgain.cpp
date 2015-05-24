/*
 * GameAgain.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GameAgain.h>
#include <Rock.h>

using namespace jupiter;
using namespace std;
using namespace glm;

GameAgain::GameAgain(int screenWidth, GameTools tools, std::function<void()> newGame): _newGame(newGame), _tools(tools)
{
    float againButtonW = screenWidth * 0.8, againButtonH = screenWidth * 0.4;

    _norm = make_shared<Sprite>(
            Texture::create(make_shared<FileTextureLoader>("resources/images/fail_again.png")),
            make_shared<RectSpriteLoader>(againButtonW, againButtonH, 1, 0.05, 0.95, 0.95, 0.52)
            );

    _pushed = make_shared<Sprite>(
            Texture::create(make_shared<FileTextureLoader>("resources/images/fail_again_pushed.png")),
            make_shared<RectSpriteLoader>(againButtonW, againButtonH, 1, 0.05, 0.95, 0.95, 0.52)
            );

    _pushed->setModelMatrix(translate(_pushed->getModelMatrix(), vec3{2.f, -2.f, 0.f}));

    _buttonRect = Rect(-againButtonW / 2, -againButtonH / 2, againButtonW / 2,
            againButtonH / 2);

#ifdef NDK_GAME_DEBUG
    _rect = make_shared<Sprite>(
            Texture::create(make_shared<AssetTextureLoader>(app, "images/white.png")),
            make_shared<RectSpriteLoader>(_buttonRect, 2, 0, 0.91, 1, 0.4)
            );
#endif

    _cur = _norm;
}

GameAgain::~GameAgain()
{
    cout << "GameAgain::~GameAgain()" << endl;
}

void GameAgain::update(double elapsed)
{
    if (_fadeOut >= 0)
    {
        _fadeOut -= elapsed;
    }
    else if (_cur == _pushed) _cur = _norm;
}

void GameAgain::input(int x, int y)
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

list<shared_ptr<jupiter::Sprite>> GameAgain::getSprites() const
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}

string GameAgain::getName() const
{
    return "GameAgain";
}
