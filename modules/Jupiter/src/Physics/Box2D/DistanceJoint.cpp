/*
 * DistanceJoint.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#include "Jupiter/Physics.h"
#include "Jupiter/DistanceJoint.h"

namespace jupiter {

DistanceJoint::DistanceJoint(Physics* visitor, b2DistanceJointDef jointDef) :
    Joint(visitor, jointDef) {
}

DistanceJoint::~DistanceJoint() {
}

b2DistanceJoint* DistanceJoint::getDistanceJoint() {
    auto joint = dynamic_cast<b2DistanceJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
