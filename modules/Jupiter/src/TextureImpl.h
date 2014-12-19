/*
 * TextureImpl.h
 *
 *  Created on: Dec 14, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_SRC_TEXTUREIMPL_H_
#define MODULES_JUPITER_SRC_TEXTUREIMPL_H_

#include <GL/glew.h>

namespace jupiter
{

class TextureImpl
{
public:
    friend class Texture;

    TextureImpl(GLuint _textureID = 0, GLenum _type = 0, uint32_t width = 0, uint32_t height = 0);
    virtual ~TextureImpl();

    virtual uint32_t getWidth() const;
    virtual uint32_t getHeight() const;

private:
    GLuint _textureID = 0;
    GLenum _type = 0;
    uint32_t _width = 0;
    uint32_t _height = 0;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_SRC_TEXTUREIMPL_H_ */
