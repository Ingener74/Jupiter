/*
 * Image.cpp
 *
 *  Created on: May 27, 2014
 *      Author: ingener
 */

#include <Engine/Image.h>

std::ostream& ndk_game::operator <<(std::ostream& sout, const Image& image)
{
    sout << "Image: " << image.width << " x " << image.height << ", "
            << (image.type == Image::Type::RGB) ? "RGB" : "RGBA";
    return sout;
}

