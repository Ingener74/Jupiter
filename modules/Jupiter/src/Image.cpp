/*
 * Image.cpp
 *
 *  Created on: May 27, 2014
 *      Author: ingener
 */

#include "Jupiter/Image.h"

namespace jupiter {

using namespace std;

int Image::getWidth() const {
    return _width;
}

int Image::getHeight() const {
    return _height;
}

const void* Image::getData() const {
    return data.data();
}

Image::Type Image::getType() const {
    return type;
}

std::ostream& operator <<(std::ostream& out, const Image& r) {
    return out << "Image: " << r._width << " x " << r._height << ", "
        << (r.type == Image::Type::RGB ? std::string("RGB") : std::string("RGBA"));
}

}  // namespace jupiter
