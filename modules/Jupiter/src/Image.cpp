/*
 * Image.cpp
 *
 *  Created on: May 27, 2014
 *      Author: ingener
 */

#include <string>

#include "Jupiter/JupiterError.h"
#include "Jupiter/Image.h"

namespace jupiter {

using namespace std;

Image::Image(const std::string& name) :
    Object(name) {
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

const uint8_t* Image::getData() const {
    return data.data();
}

Image::Type Image::getType() const {
    return type;
}

ostream& operator <<(ostream& out, const Image& r) {
    return out << "Image: " << r.width << " x " << r.height << ", "
        << (r.type == Image::Type::RGB ? string("RGB") : string("RGBA"));
}

}  // namespace jupiter
