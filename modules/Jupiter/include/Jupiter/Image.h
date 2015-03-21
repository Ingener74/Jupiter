/*
 * Image.h
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#ifdef SWIG
    #pragma SWIG nowarn=503
#else
    #include <cstdint>
    #include <iostream>
    #include <vector>
    #include <memory>
#endif

namespace jupiter {

class Image {
public:
    enum class Type {
        RGB, RGBA
    };

    Image(const std::string& name);

    virtual ~Image() = default;

    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual void const* getData() const;
    virtual Image::Type getType() const;

    friend std::ostream& operator <<(std::ostream& out, const Image& r);

protected:
    int width = 0, height = 0;
    Image::Type type = Image::Type::RGB;
    std::vector<uint8_t> data;
};

inline Image::Image(const std::string& name) {
}

inline int Image::getWidth() const {
    return width;
}

inline int Image::getHeight() const {
    return height;
}

inline void const* Image::getData() const {
    return data.data();
}

inline Image::Type Image::getType() const {
    return type;
}

inline std::ostream& operator <<(std::ostream& out, const Image& r) {
    return out << "Image: " << r.width << " x " << r.height << ", "
            << (r.type == Image::Type::RGB ? std::string("RGB") : std::string("RGBA"));
}

}  // namespace ndk_game

#endif /* IMAGE_H_ */
