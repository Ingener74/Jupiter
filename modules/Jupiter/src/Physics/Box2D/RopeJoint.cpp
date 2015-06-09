/*
 * RopeJoint.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#include <Jupiter/RopeJoint.h>

namespace jupiter {

RopeJoint::RopeJoint(Box2dVisitor* visitor, b2RopeJointDef jointDef) :
    _visitor(visitor) {
    jassert(visitor, "invalid box2d visitor");
    _joint = dynamic_cast<b2RopeJoint*>(_visitor->getWorld()->CreateJoint(&jointDef));
}

RopeJoint::~RopeJoint() {
    jassert(_visitor, "no visitor");
    _visitor->getWorld()->DestroyJoint(_joint);
}

b2RopeJoint* RopeJoint::getRopeJoint() {
    jassert(_joint, "no joint");
    return _joint;
}

} /* namespace jupiter */
