/*
 * PngImage.h
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_PNGIMAGE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_PNGIMAGE_H_

#ifdef SWIG
#else
#endif

#include "Jupiter/Image.h"

namespace jupiter {

class PngImage: public Image {
public:
    PngImage(const std::string& fileName);
    virtual ~PngImage() = default;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_PNGIMAGE_H_ */
