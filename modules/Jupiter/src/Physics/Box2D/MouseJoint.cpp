/*
 * MouseJoint.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#include "Jupiter/MouseJoint.h"

namespace jupiter {

MouseJoint::MouseJoint(Physics* visitor, b2MouseJointDef jointDef) :
    Joint(visitor, jointDef) {
}

MouseJoint::~MouseJoint() {
}

b2MouseJoint* MouseJoint::getMouseJoint() {
    auto joint = dynamic_cast<b2MouseJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
