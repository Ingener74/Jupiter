/*
 * Image.cpp
 *
 *  Created on: May 27, 2014
 *      Author: ingener
 */

#include <string>

#include "../ImageImpl.h"
#include <Jupiter/detail/ImageBuilder.h>
#include <Jupiter/JupiterError.h>

#include <Jupiter/Image.h>

namespace jupiter
{

using namespace std;

Image::Image(const std::string& fileName) :
        _impl(ImageBuilder::create(fileName))
{
}

int Image::getWidth() const
{
    return _impl ? _impl->width : throw JupiterError("invalid image");
}

int Image::getHeight() const
{
    return _impl ? _impl->height : throw JupiterError("invalid image");
}

const uint8_t* Image::getData() const
{
    return _impl ? _impl->data.data() : throw JupiterError("invalid image");
}

Image::Type Image::getType() const
{
    return _impl ? _impl->type : throw JupiterError("invalid image");
}

ostream& operator <<(ostream& out, const Image& r)
{
    return out << "Image: " << *r._impl;
}

}  // namespace jupiter
