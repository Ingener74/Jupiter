/*
 * CircleShape.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: pavel
 */

#include "Jupiter/Ref.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/Image.h"
#include "Jupiter/CircleShape.h"

namespace jupiter {

CircleShape::CircleShape(Image* image, b2FixtureDef fixtureDef, float scale) :
    _fixtureDef(fixtureDef) {
    Ref<Image>{image};

    jassert(image, "image invalid");
    jassert(image->getWidth(), "image width invalid");
    jassert(image->getHeight(), "image height invalid");
    jassert(image->getData(), "image data invalid");

    _radius = scale * image->getWidth()/ 2.f;
    _shape.m_radius = _radius;
    _fixtureDef.shape = &_shape;
}

CircleShape::~CircleShape() {
}

void CircleShape::setScale(float x, float y) {
    _shape.m_radius = _radius * x;
}

int CircleShape::shapesCount() const {
    return 1;
}

b2FixtureDef* CircleShape::getFixtureDef(int index) {
    jassert(index == 0, "invalid index");
    return &_fixtureDef;
}

} /* namespace jupiter */
