/*
 * WeldJoint.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#include "Jupiter/WeldJoint.h"

namespace jupiter {

WeldJoint::WeldJoint(Box2dVisitor* visitor, b2WeldJointDef jointDef) :
    Joint(visitor, jointDef) {
}

WeldJoint::~WeldJoint() {
}

b2WeldJoint* WeldJoint::getWeldJoint() {
    auto joint = dynamic_cast<b2WeldJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
