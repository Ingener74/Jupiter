/*
 * WeldJoint.h
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_WELDJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_WELDJOINT_H_

#include "Joint.h"

namespace jupiter {

class WeldJoint: public Joint {
public:
    WeldJoint(Physics*, b2WeldJointDef);
    virtual ~WeldJoint();

    b2WeldJoint* getWeldJoint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_WELDJOINT_H_ */
