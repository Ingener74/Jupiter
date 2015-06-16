/*
 * Joint.cpp
 *
 *  Created on: 07 июня 2015 г.
 *      Author: Pavel
 */

#include "Jupiter/Physics.h"
#include "Jupiter/Joint.h"

namespace jupiter {

Joint::Joint(Physics* visitor, b2JointDef jointDef) :
    _visitor(visitor) {
    jassert(_visitor, "invalid Box2D visitor");
    _joint = _visitor->getWorld()->CreateJoint(&jointDef);
}

Joint::~Joint() {
    jassert(_visitor, "no visitor");
    _visitor->getWorld()->DestroyJoint(_joint);
}

} /* namespace jupiter */
