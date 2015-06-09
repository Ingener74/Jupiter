/*
 * GearJoint.h
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_GEARJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_GEARJOINT_H_

#ifdef SWIG
#else
#endif

#include "Joint.h"

namespace jupiter {

class GearJoint: public Joint {
public:
    GearJoint(Box2dVisitor*, b2GearJointDef);
    virtual ~GearJoint();

    b2GearJoint* getGearJoint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_GEARJOINT_H_ */
