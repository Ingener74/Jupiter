/*
 * CircleShape.h
 *
 *  Created on: Jun 3, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_CIRCLESHAPE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_CIRCLESHAPE_H_

#ifdef SWIG
#else
    #include <Box2D/Box2D.h>
#endif

#include "PhysicsShape.h"

namespace jupiter {

class Image;

class CircleShape: public PhysicsShape {
public:
    CircleShape(Image*, b2FixtureDef);
    virtual ~CircleShape();

    virtual void setScale(float x, float y);
    virtual int shapesCount() const;
    virtual b2FixtureDef* getFixtureDef(int index);

protected:
    float _radius = 0.f;
    b2FixtureDef  _fixtureDef;
    b2CircleShape _shape;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_CIRCLESHAPE_H_ */
