/*
 * Joint.h
 *
 *  Created on: 07 июня 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_JOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_JOINT_H_

#ifdef SWIG
#else
    #include <Box2D/Box2D.h>

    #include "Ref.h"
#endif

#include "Node.h"

namespace jupiter {

class Physics;

class Joint: public Node {
public:
    Joint(Physics*, b2JointDef);
    virtual ~Joint();

protected:
    Ref<Physics> _visitor;
    b2Joint*          _joint = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_JOINT_H_ */
