/*
 * CircleShape.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: pavel
 */

#include "Jupiter/JupiterError.h"
#include "Jupiter/Image.h"
#include "Jupiter/CircleShape.h"

namespace jupiter {

CircleShape::CircleShape(Image* image, b2FixtureDef fixtureDef) :
    _fixtureDef(fixtureDef) {
    jassert(image, "image invalid");
    jassert(image->getWidth(), "image width invalid");
    jassert(image->getHeight(), "image height invalid");
    jassert(image->getData(), "image data invalid");

    _shape.m_radius = image->getWidth() / 2.;
    _fixtureDef.shape = &_shape;
}

CircleShape::~CircleShape() {
}

int CircleShape::shapesCount() const {
    return 1;
}

b2FixtureDef* CircleShape::getFixtureDef(int index) {
    jassert(index == 0, "invalid index");
    return &_fixtureDef;
}

} /* namespace jupiter */
