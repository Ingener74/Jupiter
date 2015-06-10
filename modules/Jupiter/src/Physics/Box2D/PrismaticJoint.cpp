/*
 * PrismaticJoint.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#include "Jupiter/PrismaticJoint.h"

namespace jupiter {

PrismaticJoint::PrismaticJoint(Box2dVisitor* visitor, b2PrismaticJointDef jointDef) :
    Joint(visitor, jointDef) {
}

PrismaticJoint::~PrismaticJoint() {
}

b2PrismaticJoint* PrismaticJoint::getPrismaticJoint() {
    auto joint = dynamic_cast<b2PrismaticJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
