/*
 * PrismaticJoint.h
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_PRISMATICJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_PRISMATICJOINT_H_

#include "Joint.h"

namespace jupiter {

class PrismaticJoint: public Joint {
public:
    PrismaticJoint(Physics*, b2PrismaticJointDef);
    virtual ~PrismaticJoint();

    b2PrismaticJoint* getPrismaticJoint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_PRISMATICJOINT_H_ */
