/*
 * Sprite.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <Engine/Sprite.h>

namespace ndk_game
{

Sprite::Sprite(Texture::Ptr texture) :
        _texture(texture)
{
}

Sprite::~Sprite()
{
}

Texture::Ptr Sprite::getTexture() const throw ()
{
    return _texture;
}

float* Sprite::getMesh() const throw ()
{
    return _data.get();
}

} /* namespace ndk_game */
