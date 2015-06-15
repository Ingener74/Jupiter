/*
 * WheelJoint.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#include "Jupiter/Physics.h"
#include "Jupiter/WheelJoint.h"

namespace jupiter {

WheelJoint::WheelJoint(Physics* visitor, b2WheelJointDef jointDef) :
    Joint(visitor, jointDef) {
}

WheelJoint::~WheelJoint() {
}

b2WheelJoint* WheelJoint::getWheelJoint() {
    auto joint = dynamic_cast<b2WheelJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
