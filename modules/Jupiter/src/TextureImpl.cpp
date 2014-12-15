/*
 * TextureImpl.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: ingener
 */

#include <Jupiter/Tools.h>

#include "TextureImpl.h"

namespace jupiter
{

TextureImpl::TextureImpl( GLuint textureID, GLenum type ): _textureID(textureID), _type(type)
{
}

TextureImpl::~TextureImpl()
{
    glDeleteTextures(1, &_textureID);
    Tools::glError();
}

} /* namespace jupiter */
