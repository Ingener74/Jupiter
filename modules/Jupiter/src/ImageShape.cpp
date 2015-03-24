/*
 * ImageShape.cpp
 *
 *  Created on: 20 марта 2015 г.
 *      Author: pavel
 */

#include "Jupiter/Tools.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/Image.h"
#include "Jupiter/ImageShape.h"

namespace jupiter {

using namespace std;

ImageShape::ImageShape(Image* image) {

    /*
     * -w/2                  w/2
     *
     *   0                   1     h/2     texW
     *
     *
     *   2                   3    -h/2
     *
     *
     *
     *
     *   texH
     */

    float h = image->getHeight(), w = image->getWidth();
    float l = Tools::upperPowerOfTwo(max(h, w));
    float z = 0.f;

    data = {
        -w/2,  h/2, z,    0.f, 0.f,
         w/2,  h/2, z,    w/l, 0.f,
        -w/2, -h/2, z,    0.f, h/l,
         w/2, -h/2, z,    w/l, h/l,
    };
    components = { {"aPOS", {3, &data[0]}}, {"aTEX", {2, &data[3]}}};
    type = TRIANGLE_STRIP;
}

ImageShape::~ImageShape() {
}

} /* namespace jupiter */
