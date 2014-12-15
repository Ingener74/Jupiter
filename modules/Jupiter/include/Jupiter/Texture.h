/*
 * Texture.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <memory>
#include <GL/glew.h>

namespace jupiter
{

class TextureImpl;

class Texture
{
public:
    Texture(const std::string& texture);

    void bind();

private:
    std::shared_ptr<TextureImpl> _impl;
};

} /* namespace ndk_game */

#endif /* TEXTURE_H_ */
