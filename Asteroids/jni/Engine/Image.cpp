/*
 * Image.cpp
 *
 *  Created on: May 27, 2014
 *      Author: ingener
 */

#include <Engine/Image.h>

std::ostream& ndk_game::operator <<(std::ostream& sout, const Image& image)
{
    std::string type = (image.type == Image::Type::RGB) ? "RGB" : "RGBA";
    sout << "Image: " << image.width << " x " << image.height << ", " << type;
    return sout;
}

