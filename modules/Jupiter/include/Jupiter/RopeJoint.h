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
#endif

#include "Joint.h"

namespace jupiter {

class RopeJoint: public Joint {
public:
    RopeJoint(Physics*, b2RopeJointDef);
    virtual ~RopeJoint();

    b2RopeJoint* getRopeJoint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_ROPEJOINT_H_ */
