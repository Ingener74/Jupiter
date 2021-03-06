/*
 * PoligonShape.h
 *
 *  Created on: 02 июня 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_POLIGONSHAPE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_POLIGONSHAPE_H_

#ifdef SWIG
#else
    #include <Box2D/Box2D.h>
#endif

#include "PhysicsShape.h"

namespace jupiter {

class Image;

class PoligonShape: public PhysicsShape {
public:
    PoligonShape(Image*, b2FixtureDef);
    virtual ~PoligonShape();

    virtual void setScale(float x, float y);
    virtual float getScaleX() const;
    virtual float getScaleY() const;
    virtual int shapesCount() const;
    virtual b2FixtureDef* getFixtureDef(int index);

protected:
    float _width = 0.f, _height = 0.f, _scaleX = 1.f, _scaleY = 1.f;
    b2FixtureDef   _fixtureDef;
    b2PolygonShape _shape;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_POLIGONSHAPE_H_ */
