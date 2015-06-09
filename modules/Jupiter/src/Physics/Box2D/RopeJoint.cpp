/*
 * RopeJoint.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#include "Jupiter/Box2dVisitor.h"
#include "Jupiter/RopeJoint.h"

namespace jupiter {

RopeJoint::RopeJoint(Box2dVisitor* visitor, b2RopeJointDef jointDef) :
    Joint(visitor) {
    _joint = _visitor->getWorld()->CreateJoint(&jointDef);
}

RopeJoint::~RopeJoint() {
}

b2RopeJoint* RopeJoint::getRopeJoint() {
    auto joint = dynamic_cast<b2RopeJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
