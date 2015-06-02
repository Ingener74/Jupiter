/*
 * PhysicsShape.cpp
 *
 *  Created on: 02 июня 2015 г.
 *      Author: Pavel
 */

#include "Jupiter/PhysicsShape.h"

namespace jupiter {

PhysicsShape::PhysicsShape() {
}

PhysicsShape::~PhysicsShape() {
}

b2Shape* PhysicsShape::getShape() {
    return _shape.get();
}

} /* namespace jupiter */
