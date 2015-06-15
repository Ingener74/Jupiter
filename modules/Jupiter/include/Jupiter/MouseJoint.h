/*
 * MouseJoint.h
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_MOUSEJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_MOUSEJOINT_H_

#include "Joint.h"

namespace jupiter {

class MouseJoint: public Joint {
public:
    MouseJoint(Physics*, b2MouseJointDef);
    virtual ~MouseJoint();

    b2MouseJoint* getMouseJoint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_MOUSEJOINT_H_ */
