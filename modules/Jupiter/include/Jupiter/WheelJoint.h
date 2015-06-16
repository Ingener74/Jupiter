/*
 * WheelJoint.h
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_WHEELJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_WHEELJOINT_H_

#ifdef SWIG
#else
#endif

#include "Joint.h"

namespace jupiter {

class WheelJoint: public Joint {
public:
    WheelJoint(Physics*, b2WheelJointDef);
    virtual ~WheelJoint();

    b2WheelJoint* getWheelJoint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_WHEELJOINT_H_ */
