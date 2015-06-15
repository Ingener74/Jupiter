/*
 * ComplexShape.cpp
 *
 *  Created on: 03 июня 2015 г.
 *      Author: Pavel
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "Jupiter/Ref.h"
#include "Jupiter/File.h"
#include "Jupiter/Image.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/ComplexShape.h"

namespace jupiter {

using namespace std;

ComplexShape::ComplexShape() {
}

ComplexShape::ComplexShape(Image* image, PhysicsBodyEditorShape shape, b2FixtureDef fixtureDef) :
    _shape(shape), _fixtureDef(fixtureDef) {
    jassert(image, "invalid image");
    Ref<Image> { image };

    _width = image->getWidth();
    _height = image->getHeight();

    setScale(1, 1);
}

ComplexShape::~ComplexShape() {
}

void ComplexShape::setScale(float x, float y) {
    jassert(!_shape.polygons.empty() || !_shape.circles.empty(), "invalid polygons or circles");
    _polygonShapes.clear();
    _circleShapes.clear();

    float w = 1.f;
    float h = float(_height) / float(_width);

    for (auto poligon : _shape.polygons) {
        vector<b2Vec2> poly;
        for (auto point : poligon)
            poly.emplace_back(_width * w * point.x * x, _height * h * point.y * y);

        b2PolygonShape shape;
        shape.Set(poly.data(), poly.size());
        _polygonShapes.push_back(shape);
    }

    for (auto circle : _shape.circles) {
        b2CircleShape shape;
        shape.m_radius = circle.radius;
        _circleShapes.push_back(shape);
    }
}

int ComplexShape::shapesCount() const {
    jassert(!_polygonShapes.empty() || !_circleShapes.empty(), "invalid polygons or circles");
    return _polygonShapes.size() + _circleShapes.size();
}

b2FixtureDef* ComplexShape::getFixtureDef(int index) {
    jassert(index >= 0 && index < shapesCount(), "invalid index");
    if (index < _polygonShapes.size()) {
        _fixtureDef.shape = &_polygonShapes.at(index);
    } else {
        _fixtureDef.shape = &_circleShapes.at(_polygonShapes.size() - index);
    }
    return &_fixtureDef;
}

} /* namespace jupiter */

