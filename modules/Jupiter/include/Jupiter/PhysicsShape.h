/*
 * PhysicsShape.h
 *
 *  Created on: 02 июня 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_PHYSICSSHAPE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_PHYSICSSHAPE_H_

#ifdef SWIG
#else
    #include <Box2D/Box2D.h>
#endif

class b2Shape;

namespace jupiter {

class PhysicsShape {
public:
    PhysicsShape();
    virtual ~PhysicsShape();

    b2Shape* getShape();

protected:
    std::unique_ptr<b2Shape> _shape;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_PHYSICSSHAPE_H_ */
