/*
 * BackGround.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: pavel
 */

#include "BackGround.h"

BackGround::BackGround(std::function<std::string()> getGameLocation)
{
    auto textureLoader = std::make_shared<jupiter::FileTextureLoader>(
            getGameLocation() + "/resources/images/rocks1.png");

    auto texture = jupiter::Texture::create(textureLoader);

    auto rect = std::make_shared<jupiter::RectSpriteLoader>(100, 100, 0, 0, 1, 0, 1);

    background = std::make_shared<jupiter::Sprite>(texture, rect);
}

void BackGround::update(double elapsed)
{
    throw jupiter::JupiterError("test");
}

std::list<std::shared_ptr<jupiter::Sprite> > BackGround::getSprites() const
{
    return {background};
}

std::string BackGround::getName() const
{
    return "Test Background";
}
