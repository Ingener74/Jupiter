/*
 * Texture.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <Jupiter/Tools.h>
#include <Jupiter/Texture.h>
#include <Jupiter/TextureBuilder.h>

#include "../TextureImpl.h"

namespace jupiter
{

using namespace std;

//Texture::Texture(const std::string& texture) :
//        _impl(TextureBuilder::create(texture))
//{
//}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, _textureID);
    Tools::glError();
}

int Texture::getWidth() const
{
    return _width;
}

int Texture::getHeight() const
{
    return _height;
}

} /* namespace ndk_game */

