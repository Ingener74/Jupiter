/*
 * ImageTexture.h
 *
 *  Created on: 19 марта 2015 г.
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_IMAGETEXTURE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_IMAGETEXTURE_H_

#include "Texture.h"

namespace jupiter {

class ImageTexture: public Texture {
public:
    ImageTexture(class Image*);
    virtual ~ImageTexture();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_IMAGETEXTURE_H_ */
