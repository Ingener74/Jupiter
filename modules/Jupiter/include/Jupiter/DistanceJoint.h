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
#endif

#include "Joint.h"

namespace jupiter {

class Physics;

class DistanceJoint: public Joint {
public:
    DistanceJoint(Physics*, b2DistanceJointDef);
    virtual ~DistanceJoint();

    b2DistanceJoint* getDistanceJoint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_DISTANCEJOINT_H_ */
