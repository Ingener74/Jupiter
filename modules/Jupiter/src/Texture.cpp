/*
 * Texture.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <Jupiter/Tools.h>
#include <Jupiter/TextureLoader.h>
#include <Jupiter/Texture.h>

namespace ndk_game
{

Texture::Ptr Texture::create(TextureLoader::Ptr textureLoader)
{
    auto texture = std::shared_ptr<Texture>(new Texture);

    glGenTextures(1, &texture->_textureID);
    Tools::glError();

    glBindTexture(GL_TEXTURE_2D, texture->_textureID);
    Tools::glError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    auto im = textureLoader->load();
    texture->_type = ((im.type == Image::Type::RGBA) ? GL_RGBA : GL_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, texture->_type, im.width, im.height, 0,
            texture->_type, GL_UNSIGNED_BYTE, im.data.get());
    Tools::glError();

    return texture;
}

Texture::~Texture()
{
    glDeleteTextures(1, &_textureID);
    Tools::glError();
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, _textureID);
    Tools::glError();
}

Texture::Texture() :
        _textureID(0), _type(GL_RGBA)
{
}

} /* namespace ndk_game */

