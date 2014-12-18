/*
 * SpriteImpl.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include "SpriteImpl.h"

namespace jupiter
{

SpriteImpl::SpriteImpl()
{
}

SpriteImpl::SpriteImpl( const Texture& texture, const Shape& shape ) :
        _texture(texture), _shape(shape)
{
}

SpriteImpl::~SpriteImpl()
{
}

} /* namespace jupiter */
