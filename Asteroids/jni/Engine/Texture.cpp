/*
 * Texture.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <Engine/Tools.h>
#include <Engine/Texture.h>

namespace ndk_game
{

Texture::Ptr Texture::create()
{
    auto texture = std::shared_ptr<Texture>(new Texture);

    glGenTextures(1, &texture->_textureID);
    Tools::glError();

    return texture;
}

Texture::~Texture()
{
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

Texture::Texture() :
        _textureID(0)
{
}

} /* namespace ndk_game */

