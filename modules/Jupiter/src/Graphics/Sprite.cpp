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

#include <Jupiter/SpriteBuilder.h>

namespace jupiter
{

using namespace std;

Sprite::Sprite(const std::string& sprite) throw (JupiterError) :
        _impl(SpriteBuilder::create(sprite))
{
}

} /* namespace ndk_game */
