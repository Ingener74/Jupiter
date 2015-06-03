/*
 * PoligonShape.cpp
 *
 *  Created on: 02 июня 2015 г.
 *      Author: Pavel
 */

#include "Jupiter/Tools.h"
#include "Jupiter/Image.h"
#include "Jupiter/PoligonShape.h"

namespace jupiter {

PoligonShape::PoligonShape(Image* image, b2FixtureDef fixtureDef) :
    _fixtureDef(fixtureDef) {
    jassert(image, "image invalid");
    jassert(image->getWidth(), "image width invalid");
    jassert(image->getHeight(), "image height invalid");
    jassert(image->getData(), "image data invalid");

    _shape.SetAsBox(image->getWidth() / 2, image->getHeight() / 2);
    _fixtureDef.shape = &_shape;
}

PoligonShape::~PoligonShape() {
}

int PoligonShape::shapesCount() const {
    return 1;
}

b2FixtureDef* PoligonShape::getFixtureDef(int index) {
    jassert(index == 0, "invalid index");
    return &_fixtureDef;
}

} /* namespace jupiter */
