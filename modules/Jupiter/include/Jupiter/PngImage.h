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
    #include <memory>
    #include <png.h>
#endif

#include "Jupiter/Image.h"

namespace jupiter {

class File;

class PngImage: public Image {
public:
    PngImage(const std::string& fileName);
    virtual ~PngImage() = default;

    static void pngRwCallback(png_structp, png_bytep, png_size_t);

private:
    std::unique_ptr<File> file;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_PNGIMAGE_H_ */
