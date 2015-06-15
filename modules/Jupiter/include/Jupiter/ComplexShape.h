/*
 * ComplexShape.h
 *
 *  Created on: 03 июня 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_COMPLEXSHAPE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_COMPLEXSHAPE_H_

#ifdef SWIG
#else
    #include <json.hpp>
#endif

#include "PhysicsBodyEditorAtlas.h"
#include "PhysicsShape.h"

namespace jupiter {

class PhysicsBodyEditorShape;
class Image;

class ComplexShape: public PhysicsShape {
public:
    ComplexShape();
    ComplexShape(Image*, PhysicsBodyEditorShape, b2FixtureDef);
    virtual ~ComplexShape();

    virtual void setScale(float x, float y);
    virtual int shapesCount() const;
    virtual b2FixtureDef* getFixtureDef(int index);

protected:
    int                           _width = 0;
    int                           _height = 0;
    PhysicsBodyEditorShape        _shape;

    b2FixtureDef                  _fixtureDef;
    std::vector<b2PolygonShape>   _polygonShapes;
    std::vector<b2CircleShape>    _circleShapes;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_COMPLEXSHAPE_H_ */
