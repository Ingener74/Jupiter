/*
 * ImageShape.h
 *
 *  Created on: 20 марта 2015 г.
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_IMAGESHAPE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_IMAGESHAPE_H_

#include "Shape.h"

namespace jupiter {

class ImageShape: public Shape {
public:
    ImageShape(class Image*, float z = 0.f);
    virtual ~ImageShape();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_IMAGESHAPE_H_ */
