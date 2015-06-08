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

    #include "RCO.h"
#endif

namespace jupiter {

class Image: virtual public RCO {
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
    int _width = 0, _height = 0;
    Image::Type type = Image::Type::RGB;
    std::vector<uint8_t> data;
};

inline Image::Image(const std::string& name) {
}

}  // namespace ndk_game

#endif /* IMAGE_H_ */
