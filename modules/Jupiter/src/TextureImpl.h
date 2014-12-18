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

    TextureImpl(GLuint _textureID = 0, GLenum _type = 0);
    virtual ~TextureImpl();

private:
    GLuint _textureID = 0;
    GLenum _type = 0;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_SRC_TEXTUREIMPL_H_ */
