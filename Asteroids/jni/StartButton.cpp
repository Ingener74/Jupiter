/*
 * StartButton.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <StartButton.h>

using namespace ndk_game;

StartButton::StartButton(android_app * app, int screenWidth,
        IDrawEngine::Ptr engine, Scene::Ptr mainScene) :
        _engine(engine), _mainScene(mainScene)
{
    float startButtonW = screenWidth * 0.4, startButtonH = screenWidth * 0.1;

    _sb1 = std::make_shared<Sprite>(
            Texture::create(std::make_shared<AssetTextureLoader>(app, "images/start.png")),
            std::make_shared<RectSpriteLoader>(startButtonW, startButtonH, 1, 0, 0.91, 0.95, 0.65)
            );

    _sb2 = std::make_shared<Sprite>(
            Texture::create(std::make_shared<AssetTextureLoader>(app, "images/start_pushed.png")),
            std::make_shared<RectSpriteLoader>(startButtonW, startButtonH, 1, 0, 0.91, 0.95, 0.65)
            );

    _sb2->getModelMatrix() = glm::translate(_sb2->getModelMatrix(),
            glm::vec3(2.f, -2.f, 0.f));

    _buttonRect = Rect(-startButtonW / 2, -startButtonH / 2, startButtonW / 2,
            startButtonH / 2);

#ifdef NDK_GAME_DEBUG
    _rect = std::make_shared<Sprite>(
            Texture::create(std::make_shared<AssetTextureLoader>(app, "images/white.png")),
            std::make_shared<RectSpriteLoader>(_buttonRect, 2, 0, 0.91, 1, 0.4)
            );
#endif

    _cur = _sb1;
}

void StartButton::update(double elapsed) throw (std::runtime_error)
{
//    _cur->getModelMatrix() = glm::translate(_cur->getModelMatrix(), glm::vec3(1.f, 0.f, 0.f));
//    _cur->getModelMatrix() = glm::rotate(_cur->getModelMatrix(), 0.005f, glm::vec3(0.f, 0.f, 1.f));
}
void StartButton::input(int x, int y) throw (std::runtime_error)
{
    if (_buttonRect.isInside(x, y))
    {
        _cur = _sb2;

        if (!_engine || !_mainScene) throw std::runtime_error(
                "engine or main scene is null");
        _engine->setCurrentScene(_mainScene);
    }
    else
    {
        _cur = _sb1;
    }
}
std::list<Sprite::Ptr> StartButton::getSprites() const throw ()
{
#ifdef NDK_GAME_DEBUG
    return {_cur, _rect};
#else
    return {_cur};
#endif
}

