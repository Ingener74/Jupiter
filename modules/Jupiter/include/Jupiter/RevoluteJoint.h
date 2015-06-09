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
#endif

#include "Joint.h"

namespace jupiter {

class RevoluteJoint: public Joint {
public:
    RevoluteJoint(Box2dVisitor*, b2RevoluteJointDef);
    virtual ~RevoluteJoint();

    b2RevoluteJoint* getRevoluteJoint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_REVOLUTEJOINT_H_ */
