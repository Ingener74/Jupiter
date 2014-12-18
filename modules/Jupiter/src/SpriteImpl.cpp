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

SpriteImpl::SpriteImpl(const Texture& texture, const Shape& shape, const glm::mat4& model) :
        _texture(texture), _shape(shape), _modelMatrix(model)
{
}

SpriteImpl::~SpriteImpl()
{
}

} /* namespace jupiter */
