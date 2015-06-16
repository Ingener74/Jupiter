/*
 * FrictionJoint.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#include "Jupiter/FrictionJoint.h"

namespace jupiter {

FrictionJoint::FrictionJoint(Physics* visitor, b2FrictionJointDef jointDef) :
    Joint(visitor, jointDef) {
}

FrictionJoint::~FrictionJoint() {
}

b2FrictionJoint* FrictionJoint::getFrictionJoint() {
    auto joint = dynamic_cast<b2FrictionJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
