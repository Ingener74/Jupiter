/*
 * DistanceJoint.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#include "Jupiter/Box2dVisitor.h"
#include "Jupiter/DistanceJoint.h"

namespace jupiter {

DistanceJoint::DistanceJoint(Box2dVisitor* v, b2DistanceJointDef jointDef) :
    _visitor(v) {
    _joint = dynamic_cast<b2DistanceJoint*>(_visitor->getWorld()->CreateJoint(&jointDef));
}

DistanceJoint::~DistanceJoint() {
    jassert(_visitor, "no visitor");
    _visitor->getWorld()->DestroyJoint(_joint);
}

b2DistanceJoint* DistanceJoint::getDistanceJoint() {
    jassert(_joint, "no joint");
    return _joint;
}

} /* namespace jupiter */
