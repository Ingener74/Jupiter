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

class Box2dVisitor;

class Joint: virtual public Node {
public:
    Joint(Box2dVisitor*);
    virtual ~Joint();

protected:
    Ref<Box2dVisitor> _visitor;
    b2Joint*          _joint = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_JOINT_H_ */
