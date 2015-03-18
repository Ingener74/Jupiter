
#ifndef TEXTURE_H_
#define TEXTURE_H_

#ifdef SWIG
    namespace jupiter {
    }  // namespace jupiter
#else
    #include <GL/glew.h>
#endif

namespace jupiter
{

class Texture
{
public:
    Texture() = default;
    virtual ~Texture() = default;

    void bind() const;

    int getWidth() const;
    int getHeight() const;

private:
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
