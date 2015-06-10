/*
 * PulleyJoint.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#include "Jupiter/PulleyJoint.h"

namespace jupiter {

PulleyJoint::PulleyJoint(Box2dVisitor* visitor, b2PulleyJointDef jointDef) :
    Joint(visitor, jointDef) {
}

PulleyJoint::~PulleyJoint() {
}

b2PulleyJoint* PulleyJoint::getPulleyJoint() {
    auto joint = dynamic_cast<b2PulleyJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
