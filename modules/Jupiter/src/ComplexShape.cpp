/*
 * ComplexShape.cpp
 *
 *  Created on: 03 июня 2015 г.
 *      Author: Pavel
 */

#include <vector>

#include <json.hpp>

#include "Jupiter/File.h"
#include "Jupiter/Image.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/ComplexShape.h"

namespace jupiter {

using namespace std;
using namespace nlohmann;

ComplexShape::ComplexShape() {
}

ComplexShape::ComplexShape(Image* image, File* file, const std::string& name, b2FixtureDef fixtureDef) :
    _fixtureDef(fixtureDef) {

    jassert(image, "invalid image");
    jassert(file, "invalid file");
    jassert(!name.empty(), "invalid name");

    json j;
    file->getStream() >> j;

    float w = image->getWidth(), h = image->getHeight();

    for (auto rigidBody : j["rigidBodies"]) {
        if (rigidBody["name"] == name) {
            float Ox = rigidBody["origin"]["x"];
            float Oy = rigidBody["origin"]["y"];

            for (auto poligon : rigidBody["polygons"]) {

                vector<b2Vec2> poly;

                for (auto point : poligon) {
                    float x = point["x"];
                    float y = point["y"];
                    poly.emplace_back(x * w, y * h);
                }

                cout << "---" << endl;
                for(auto i: poly)
                    cout << i.x << "," << i.y << endl;
                cout << "---" << endl;

                _polygons.push_back(poly);

                b2PolygonShape shape;
                shape.Set(poly.data(), poly.size());
                _polygonShapes.push_back(shape);
            }
            return;
        }
    }
    jassert(false, "no shape in file");
}

ComplexShape::~ComplexShape() {
}

void ComplexShape::setScale(float x, float y) {
    jassert(false, "not implemented");
}

int ComplexShape::shapesCount() const {
    jassert(!_polygonShapes.empty(), "invalid polygons");
    return _polygonShapes.size();
}

b2FixtureDef* ComplexShape::getFixtureDef(int index) {
    jassert(index >= 0 && index < _polygonShapes.size(), "invalid index");
    _fixtureDef.shape = &_polygonShapes.at(index);
    return &_fixtureDef;
}

} /* namespace jupiter */
