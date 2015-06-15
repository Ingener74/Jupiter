/*
 * GearJoint.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#include "Jupiter/GearJoint.h"

namespace jupiter {

GearJoint::GearJoint(Physics* visitor, b2GearJointDef jointDef) :
    Joint(visitor, jointDef) {
}

GearJoint::~GearJoint() {
}

b2GearJoint* GearJoint::getGearJoint() {
    auto joint = dynamic_cast<b2GearJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
