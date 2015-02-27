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

#include "Jupiter/Aware.h"

namespace jupiter
{

class Texture: public Object
{
public:
    Texture() = default;
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
