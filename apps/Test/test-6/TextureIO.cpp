/*
 * TextureIO.cpp
 *
 *  Created on: Aug 27, 2015
 *      Author: pavel
 */

#include "TextureIO.h"

TextureIO::TextureIO() {
}

TextureIO::TextureIO(In* image) :
    _image(image) {
}

TextureIO::~TextureIO() {
}

In* TextureIO::getImage() {
    return _image;
}

void TextureIO::setImage(In* image) {
    _image = image;
}
