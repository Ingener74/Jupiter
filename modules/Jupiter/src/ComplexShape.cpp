/*
 * ComplexShape.cpp
 *
 *  Created on: 03 июня 2015 г.
 *      Author: Pavel
 */

#include <fstream>
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

//    json j;
////    ifstream f("/home/pavel/workspace/Jupiter/samples/Box/Resources/Box.json");
//    ifstream f("/home/pavel/workspace/Jupiter/samples/Box/Box.json");
//    f >> j;
//
//    string test = j["Test"];
//    cout << "test " << test << endl;
//
//    int number = j["Number"];
//    cout << "number" << number << endl;
//
//    float foo = j["Foo"];
//    cout << "foo " << foo << endl;
//
//    jassert(false, "foo");

//    ,
//        "Number":100,
//        "Foo":42.42

    json j;
    file->getStream() >> j;

    cout << "json " << endl << j << endl;

    float w = image->getWidth();
    float h = image->getHeight();

    for (auto const& rigidBody : j["rigidBodies"]) {
        if (rigidBody["name"] == name) {
            float Ox = rigidBody["origin"]["x"];
            float Oy = rigidBody["origin"]["y"];

            for (auto const& poligon : rigidBody["polygons"]) {

                vector<b2Vec2> poly;

                for (auto point : poligon) {
                    float x = point["x"];
                    float y = point["y"];
                    poly.emplace_back(x * w, y * h);
                }

                _polygons.push_back(poly);

                setScale(1, 1);
            }
            return;
        }
    }
    jassert(false, "no shape with name " + name);
}

ComplexShape::~ComplexShape() {
}

void ComplexShape::setScale(float x, float y) {
    jassert(!_polygons.empty(), "invalid polygons");
    _polygonShapes.clear();

    for (auto poligon : _polygons) {

        vector<b2Vec2> poly;

        for (auto point : poligon)
            poly.emplace_back(point.x * x, point.y * y);

        b2PolygonShape shape;
        shape.Set(poly.data(), poly.size());
        _polygonShapes.push_back(shape);
    }
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
