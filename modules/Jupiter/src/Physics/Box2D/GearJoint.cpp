/*
 * GearJoint.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#include "Jupiter/Box2dVisitor.h"
#include "Jupiter/GearJoint.h"

namespace jupiter {

GearJoint::GearJoint(Box2dVisitor* visitor, b2GearJointDef jointDef) :
    Joint(visitor) {
    _joint = _visitor->getWorld()->CreateJoint(&jointDef);
}

GearJoint::~GearJoint() {
}

b2GearJoint* GearJoint::getGearJoint() {
    auto joint = dynamic_cast<b2GearJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
