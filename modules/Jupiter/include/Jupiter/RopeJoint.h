/*
 * RopeJoint.h
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_ROPEJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_ROPEJOINT_H_

#ifdef SWIG
#else
    #include <Box2D/Box2D.h>
#endif

#include "Joint.h"

namespace jupiter {

class Box2dVisitor;

class RopeJoint: public Joint {
public:
    RopeJoint(Box2dVisitor*, b2RopeJointDef);
    virtual ~RopeJoint();

    b2RopeJoint* getRopeJoint();
protected:
    b2RopeJoint* _joint = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_ROPEJOINT_H_ */
