/*
 * PoligonShape.cpp
 *
 *  Created on: 02 июня 2015 г.
 *      Author: Pavel
 */

#include "Jupiter/Ref.h"
#include "Jupiter/Tools.h"
#include "Jupiter/Image.h"
#include "Jupiter/PoligonShape.h"

namespace jupiter {

PoligonShape::PoligonShape(Image* image, b2FixtureDef fixtureDef) :
    _fixtureDef(fixtureDef) {
    Ref<Image>{image};

    jassert(image, "image invalid");
    jassert(image->getWidth(), "image width invalid");
    jassert(image->getHeight(), "image height invalid");
    jassert(image->getData(), "image data invalid");

    _width = image->getWidth() / 2;
    _height = image->getHeight() / 2;

    _shape.SetAsBox(_width, _height);
    _fixtureDef.shape = &_shape;
}

PoligonShape::~PoligonShape() {
}

void PoligonShape::setScale(float x, float y) {
    _shape.SetAsBox(_width * x, _height * x);
}

int PoligonShape::shapesCount() const {
    return 1;
}

b2FixtureDef* PoligonShape::getFixtureDef(int index) {
    jassert(index == 0, "invalid index");
    return &_fixtureDef;
}

} /* namespace jupiter */
