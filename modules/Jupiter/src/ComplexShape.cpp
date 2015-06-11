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

#include <json.hpp>

#include "Jupiter/Ref.h"
#include "Jupiter/File.h"
#include "Jupiter/Image.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/ComplexShape.h"

namespace jupiter {

using namespace std;
using namespace nlohmann;

ComplexShape::ComplexShape() {
}

ComplexShape::ComplexShape(Image* image, PhysicsBodyEditorShape shape, b2FixtureDef fixtureDef) :
    _shape(shape), _fixtureDef(fixtureDef) {
    Ref<Image>{image};
}

ComplexShape::~ComplexShape() {
}

void ComplexShape::setScale(float x, float y) {
//    jassert(!_polygons.empty(), "invalid polygons");
//    _polygonShapes.clear();
//
//    for (auto poligon : _polygons) {
//
//        vector<b2Vec2> poly;
//
//        for (auto point : poligon)
//            poly.emplace_back(point.x * x, point.y * y);
//
//        b2PolygonShape shape;
//        shape.Set(poly.data(), poly.size());
//        _polygonShapes.push_back(shape);
//    }
}

int ComplexShape::shapesCount() const {
//    jassert(!_polygonShapes.empty(), "invalid polygons");
//    return _polygonShapes.size();
}

b2FixtureDef* ComplexShape::getFixtureDef(int index) {
//    jassert(index >= 0 && index < _polygonShapes.size(), "invalid index");
//    _fixtureDef.shape = &_polygonShapes.at(index);
//    return &_fixtureDef;
}

} /* namespace jupiter */

