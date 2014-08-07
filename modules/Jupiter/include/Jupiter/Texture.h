/*
 * Texture.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <Jupiter/Common.h>
#include <Jupiter/TextureLoader.h>

namespace jupiter
{

class Texture
{
public:
    using Ptr = std::shared_ptr<Texture>;

    static Texture::Ptr create(TextureLoader::Ptr);
    virtual ~Texture();

    virtual void bind();

private:
    Texture();

    GLuint _textureID;
    GLenum _type;
};

} /* namespace ndk_game */

#endif /* TEXTURE_H_ */
