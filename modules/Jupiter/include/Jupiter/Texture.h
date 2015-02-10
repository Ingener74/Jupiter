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
    Texture() = default;
//    Texture(const std::string& texture);
    virtual ~Texture() = default;

    void bind() const;

    int getWidth() const;
    int getHeight() const;

private:
    GLuint _textureID = 0;
    GLenum _type = 0;
    uint32_t _width = 0;
    uint32_t _height = 0;
};

} /* namespace ndk_game */

#endif /* TEXTURE_H_ */
