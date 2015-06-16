/*
 * FrictionJoint.h
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_FRICTIONJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_FRICTIONJOINT_H_

#include "Joint.h"

namespace jupiter {

class FrictionJoint: public Joint {
public:
    FrictionJoint(Physics*, b2FrictionJointDef);
    virtual ~FrictionJoint();

    b2FrictionJoint* getFrictionJoint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_FRICTIONJOINT_H_ */
