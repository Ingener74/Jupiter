
#ifndef TEXTURE_H_
#define TEXTURE_H_

#ifdef SWIG
#else

    #include <CrossPlatformOpenGL.h>

#endif

#include "RCO.h"

namespace jupiter
{

class Texture: virtual public RCO
{
public:
    friend class Uniform;

    Texture() = default;
    virtual ~Texture() = default;

    void bind() const;

    int getWidth() const;
    int getHeight() const;

protected:
    GLuint textureID = 0;
    GLenum type = 0;
    uint32_t width = 0;
    uint32_t height = 0;
};

inline int Texture::getWidth() const {
    return width;
}

inline int Texture::getHeight() const {
    return height;
}

}

#endif /* TEXTURE_H_ */
