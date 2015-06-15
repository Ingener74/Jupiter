/*
 * MotorJoint.h
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_MOTORJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_MOTORJOINT_H_

#ifdef SWIG
#else
#endif

#include "Joint.h"

namespace jupiter {

class MotorJoint: public Joint {
public:
    MotorJoint(Physics*, b2MotorJointDef);
    virtual ~MotorJoint();

    b2MotorJoint* getMotorJoint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_MOTORJOINT_H_ */
