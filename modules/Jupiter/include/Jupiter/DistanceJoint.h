/*
 * DistanceJoint.h
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_DISTANCEJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_DISTANCEJOINT_H_

#ifdef SWIG
#else
    #include <Box2D/Box2D.h>
#endif

#include "Joint.h"

namespace jupiter {

class Box2dVisitor;

class DistanceJoint: public Joint {
public:
    DistanceJoint(Box2dVisitor*, b2DistanceJointDef);
    virtual ~DistanceJoint();

    b2DistanceJoint* getDistanceJoint();

protected:
    b2DistanceJoint*     _joint = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_DISTANCEJOINT_H_ */
