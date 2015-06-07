/*
 * RevoluteJoint.h
 *
 *  Created on: 07 июня 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_REVOLUTEJOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_REVOLUTEJOINT_H_

#ifdef SWIG
#else
    #include <Box2D/Box2D.h>
#endif

#include "Joint.h"

namespace jupiter {

class RevoluteJoint: public Joint {
public:
    RevoluteJoint();
    virtual ~RevoluteJoint();

protected:
    b2RevoluteJoint* _joint;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_REVOLUTEJOINT_H_ */
