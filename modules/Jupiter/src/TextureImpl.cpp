/*
 * TextureImpl.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: ingener
 */

#include "TextureImpl.h"

namespace jupiter
{

TextureImpl::TextureImpl( GLuint textureID, GLenum type ): _textureID(textureID), _type(type)
{
}

TextureImpl::~TextureImpl()
{
}

} /* namespace jupiter */
