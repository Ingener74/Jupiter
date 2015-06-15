/*
 * RopeJoint.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#include "Jupiter/Physics.h"
#include "Jupiter/RopeJoint.h"

namespace jupiter {

RopeJoint::RopeJoint(Physics* visitor, b2RopeJointDef jointDef) :
    Joint(visitor, jointDef) {
}

RopeJoint::~RopeJoint() {
}

b2RopeJoint* RopeJoint::getRopeJoint() {
    auto joint = dynamic_cast<b2RopeJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
