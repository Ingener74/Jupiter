/*
 * Sprite.cpp
 *
 *  Created on: 25 мая 2014 г.
 *      Author: Admin
 */

#include <Engine/Sprite.h>

namespace ndk_game
{

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

void Sprite::draw()
{
    _texture->bind();
    glDrawTexfOES(0, 0, 0, 0);
}

} /* namespace ndk_game */
