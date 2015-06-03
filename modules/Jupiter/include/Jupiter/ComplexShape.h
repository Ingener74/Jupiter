/*
 * ComplexShape.h
 *
 *  Created on: 03 июня 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_COMPLEXSHAPE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_COMPLEXSHAPE_H_

#include "PhysicsShape.h"

namespace jupiter {

class File;
class Image;

class ComplexShape: public PhysicsShape {
public:
    ComplexShape();
    ComplexShape(Image*, File*, std::string const& name, b2FixtureDef);
    virtual ~ComplexShape();

    virtual void setScale(float x, float y);
    virtual int shapesCount() const;
    virtual b2FixtureDef* getFixtureDef(int index);

protected:
    std::vector<std::vector<b2Vec2>>   _polygons;
    std::vector<b2PolygonShape>        _polygonShapes;
    b2FixtureDef                       _fixtureDef;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_COMPLEXSHAPE_H_ */
