/*
 * RevoluteJoint.h
 *
 *  Created on: 07 июня 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_REVOLUTEJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_REVOLUTEJOINT_H_

#ifdef SWIG
#else
#include <Box2D/Box2D.h>
#endif

#include "Joint.h"

namespace jupiter {

class Box2dVisitor;

class RevoluteJoint: public Joint {
public:
    RevoluteJoint(Box2dVisitor*, b2RevoluteJointDef);
    virtual ~RevoluteJoint();

protected:
    Box2dVisitor* _visitor = nullptr;
    b2RevoluteJoint* _joint = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_REVOLUTEJOINT_H_ */
