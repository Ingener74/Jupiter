/*
 * BackGround.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: pavel
 */

#include "BackGround.h"

using namespace std;
using namespace jupiter;

BackGround::BackGround(function<string()> getGameLocation)
{
    auto textureLoader = make_shared<FileTextureLoader>(
            getGameLocation() + "/resources/images/bg.png");

    auto texture = Texture::create(textureLoader);

    auto rect = make_shared<RectSpriteLoader>(1, 1, 0, 0, 1, 0, 1);

    background = make_shared<Sprite>(texture, rect);
}

void BackGround::update(double elapsed)
{
    throw JupiterError("test");
}

list<shared_ptr<Sprite> > BackGround::getSprites() const
{
    return {background};
}

string BackGround::getName() const
{
    return "Test Background";
}
