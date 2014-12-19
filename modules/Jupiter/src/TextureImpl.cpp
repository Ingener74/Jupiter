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

TextureImpl::TextureImpl(GLuint textureID, GLenum type, uint32_t width, uint32_t height) :
        _textureID(textureID), _type(type), _width(width), _height(0)
{
}

TextureImpl::~TextureImpl()
{
    glDeleteTextures(1, &_textureID);
    Tools::glError();
}

uint32_t TextureImpl::getWidth() const
{
    return _width;
}

uint32_t TextureImpl::getHeight() const
{
    return _height;
}

} /* namespace jupiter */
