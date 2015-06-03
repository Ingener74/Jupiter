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

    virtual void setScale(float x, float y) = 0;
    virtual int shapesCount() const = 0;
    virtual b2FixtureDef* getFixtureDef(int index) = 0;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_PHYSICSSHAPE_H_ */
