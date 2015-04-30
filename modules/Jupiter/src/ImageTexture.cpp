/*
 * ImageTexture.cpp
 *
 *  Created on: 19 марта 2015 г.
 *      Author: pavel
 */

#include "Jupiter/Tools.h"
#include "Jupiter/Image.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/ImageTexture.h"

#include <GL/glx.h>

namespace jupiter {

using namespace std;

ImageTexture::ImageTexture(Image* image) {

    auto context = glXGetCurrentContext();
    cout << "context " << context << endl;

    glGenTextures(1, &textureID);
    CHECK_GL_ERROR

    glBindTexture(GL_TEXTURE_2D, textureID);
    CHECK_GL_ERROR

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    type = image->getType() == Image::Type::RGBA ? GL_RGBA : GL_RGB;

    width = height = std::max(Tools::upperPowerOfTwo(image->getWidth()), Tools::upperPowerOfTwo(image->getHeight()));

    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, nullptr);
    CHECK_GL_ERROR

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->getWidth(), image->getHeight(), type, GL_UNSIGNED_BYTE, image->getData());
    CHECK_GL_ERROR
}

ImageTexture::~ImageTexture() {
}

} /* namespace jupiter */
