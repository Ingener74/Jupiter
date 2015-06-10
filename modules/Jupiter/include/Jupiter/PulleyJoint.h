/*
 * PulleyJoint.h
 *
 *  Created on: Jun 10, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_PULLEYJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_PULLEYJOINT_H_

#include "Joint.h"

namespace jupiter {

class PulleyJoint: public Joint {
public:
    PulleyJoint(Box2dVisitor*, b2PulleyJointDef);
    virtual ~PulleyJoint();

    b2PulleyJoint* getPulleyJoint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_PULLEYJOINT_H_ */
