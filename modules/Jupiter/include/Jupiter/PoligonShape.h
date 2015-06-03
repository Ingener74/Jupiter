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

    virtual int shapesCount() const;
    virtual b2FixtureDef* getFixtureDef(int index);

protected:
    b2FixtureDef   _fixtureDef;
    b2PolygonShape _shape;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_POLIGONSHAPE_H_ */
