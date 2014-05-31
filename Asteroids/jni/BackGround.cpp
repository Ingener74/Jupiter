/*
 * BackGround.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <BackGround.h>

using namespace ndk_game;

BackGround::BackGround(android_app * app, int screenWidth)
{
    _bg = std::make_shared<Sprite>(
            Texture::create(std::make_shared<AssetTextureLoader>(app, "images/bg.png")),
            std::make_shared<RectSpriteLoader>(screenWidth, screenWidth, 0, 0, 1, 0, 1)
            );
}

void BackGround::update(double elapsed) throw (std::runtime_error)
{
}
void BackGround::input(int x, int y) throw (std::runtime_error)
{
}
std::list<Sprite::Ptr> BackGround::getSprites() const throw ()
{
    return
    {   _bg};
}
