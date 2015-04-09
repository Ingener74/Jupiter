/*
 * PngImage.cpp
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#include "lodepng.h"

#include "Jupiter/File.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/PngImage.h"

namespace jupiter {

using namespace std;

PngImage::PngImage(const std::string& fileName) :
    Image(fileName) {
    File file { fileName };
    const auto& buf = file.getBuffer();
    type = Image::Type::RGBA;
    auto error = lodepng::decode(data, width, height, file.getBuffer(), LCT_RGBA);
    if (error)
        throw JupiterError(lodepng_error_text(error));
}

} /* namespace jupiter */
