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

class TextureLoader;

class Texture
{
public:
    static std::shared_ptr<Texture> create(std::shared_ptr<TextureLoader>);
    virtual ~Texture();

    virtual void bind();

private:
    Texture();

    GLuint _textureID;
    GLenum _type;
};

} /* namespace ndk_game */

#endif /* TEXTURE_H_ */
