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

PoligonShape::PoligonShape(Image* image) {
    _shape = make_unique_<b2PolygonShape>();
    auto shape = dynamic_cast<b2PolygonShape*>(_shape.get());

    shape->SetAsBox(image->getWidth(), image->getHeight());
}

PoligonShape::~PoligonShape() {
}

} /* namespace jupiter */
