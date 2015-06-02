/*
 * PoligonShape.h
 *
 *  Created on: 02 июня 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_POLIGONSHAPE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_POLIGONSHAPE_H_

#include "PhysicsShape.h"

namespace jupiter {

class Image;

class PoligonShape: public PhysicsShape {
public:
    PoligonShape(Image*);
    virtual ~PoligonShape();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_POLIGONSHAPE_H_ */
