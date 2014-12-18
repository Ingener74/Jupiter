/*
 * Texture.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <Jupiter/Tools.h>
#include <Jupiter/TextureLoader.h>
#include <Jupiter/Texture.h>
#include <Jupiter/TextureBuilder.h>

#include "../TextureImpl.h"

namespace jupiter
{

using namespace std;


Texture::Texture( const std::string& texture ): _impl(TextureBuilder::create(texture))
{
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, _impl->_textureID);
    Tools::glError();
}

} /* namespace ndk_game */
