/*
 * ImageTexture.cpp
 *
 *  Created on: 19 марта 2015 г.
 *      Author: pavel
 */

#include "Jupiter/Image.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/ImageTexture.h"

namespace jupiter {

ImageTexture::ImageTexture(Image*) {
    throw JupiterError("ImageTexture not implemented");
}

ImageTexture::~ImageTexture() {
}

} /* namespace jupiter */
