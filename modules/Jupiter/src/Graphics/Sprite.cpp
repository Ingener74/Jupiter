/*
 * Sprite.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <map>
#include <iostream>

#include <Jupiter/Sprite.h>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

using namespace std;

Sprite::Sprite(const std::string& sprite) throw (JupiterError) :
        _texture(sprite), _shape(sprite)
{
}

const Texture& Sprite::getTexture() const
{
    return _texture;
}

const Shape& Sprite::getShape() const
{
    return _shape;
}

} /* namespace ndk_game */
