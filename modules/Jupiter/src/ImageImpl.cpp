/*
 * ImageImpl.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: pavel
 */

#include <iostream>

#include <ImageImpl.h>

namespace jupiter
{

using namespace std;

ImageImpl::ImageImpl(int width, int height, Image::Type type, std::vector<uint8_t> data) :
        width(width), height(height), type(type), data(data)
{
}

ostream& operator <<(ostream& out, const ImageImpl& r)
{
    return out << r.width << " x " << r.height << ", " << (r.type == Image::Type::RGB ? string("RGB") : string("RGBA"));
}

} /* namespace jupiter */
