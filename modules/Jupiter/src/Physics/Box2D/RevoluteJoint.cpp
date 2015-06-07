/*
 * RevoluteJoint.cpp
 *
 *  Created on: 07 июня 2015 г.
 *      Author: Pavel
 */

#include "Jupiter/RevoluteJoint.h"

namespace jupiter {

RevoluteJoint::RevoluteJoint(Box2dVisitor* visitor, b2RevoluteJoint jointDef): _visitor(visitor) {
}

RevoluteJoint::~RevoluteJoint() {
}

} /* namespace jupiter */
