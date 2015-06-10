/*
 * RevoluteJoint.cpp
 *
 *  Created on: 07 июня 2015 г.
 *      Author: Pavel
 */

#include "Jupiter/JupiterError.h"
#include "Jupiter/Box2dVisitor.h"
#include "Jupiter/RevoluteJoint.h"

namespace jupiter {

RevoluteJoint::RevoluteJoint(Box2dVisitor* visitor, b2RevoluteJointDef jointDef) :
    Joint(visitor, jointDef) {
}

RevoluteJoint::~RevoluteJoint() {
}

b2RevoluteJoint* RevoluteJoint::getRevoluteJoint() {
    auto joint = dynamic_cast<b2RevoluteJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
