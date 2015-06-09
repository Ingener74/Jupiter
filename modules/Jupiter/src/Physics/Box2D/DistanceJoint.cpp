/*
 * DistanceJoint.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#include "Jupiter/Box2dVisitor.h"
#include "Jupiter/DistanceJoint.h"

namespace jupiter {

DistanceJoint::DistanceJoint(Box2dVisitor* visitor, b2DistanceJointDef jointDef) :
    Joint(visitor) {
    _joint = _visitor->getWorld()->CreateJoint(&jointDef);
}

DistanceJoint::~DistanceJoint() {
}

b2DistanceJoint* DistanceJoint::getDistanceJoint() {
    auto joint = dynamic_cast<b2DistanceJoint*>(_joint);
    jassert(joint, "invalid cast");
    return joint;
}

} /* namespace jupiter */
