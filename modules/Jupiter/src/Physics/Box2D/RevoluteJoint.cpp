/*
 * RevoluteJoint.cpp
 *
 *  Created on: 07 июня 2015 г.
 *      Author: Pavel
 */

#include "Jupiter/JupiterError.h"
#include "Jupiter/Box2dVisitor.h"
#include "Jupiter/RevoluteJoint.h"

namespace jupiter {

RevoluteJoint::RevoluteJoint(Box2dVisitor* visitor, b2RevoluteJointDef jointDef) :
    _visitor(visitor) {
    _joint = dynamic_cast<b2RevoluteJoint*>(_visitor->getWorld()->CreateJoint(&jointDef));
}

RevoluteJoint::~RevoluteJoint() {
    jassert(_visitor, "no visitor");
    _visitor->getWorld()->DestroyJoint(_joint);
}

} /* namespace jupiter */
