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

void Sprite::draw()
{
    _texture->bind();


}

} /* namespace ndk_game */
