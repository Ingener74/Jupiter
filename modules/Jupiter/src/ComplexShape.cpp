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

struct PhysicsEditorJsonShape {
    struct Circle {
        Circle(b2Vec2 center, float radius) :
            center(center), radius(radius) {
        }
        b2Vec2 center;
        float radius;
    };

    PhysicsEditorJsonShape(json rigidBody) {
        string n = rigidBody["name"];
        string ip = rigidBody["imagePath"];

        name = n;
        imagePath = ip;

        origin.x = rigidBody["origin"]["x"];
        origin.y = rigidBody["origin"]["y"];

        for (auto const& polygon : rigidBody["polygons"]) {
            vector<b2Vec2> poly;

            for (auto point : polygon)
                poly.emplace_back(float(point["x"]), float(point["y"]));

            polygons.push_back(poly);
        }

        for (auto const& circle : rigidBody["circles"])
            circles.emplace_back(b2Vec2 { float(circle["cx"]), float(circle["cy"]) }, float(circle["r"]));
    }

    string name;
    string imagePath;
    b2Vec2 origin;
    vector<vector<b2Vec2>> polygons;
    vector<Circle> circles;

    friend ostream& operator<<(ostream& out, const b2Vec2& r) {
        return out << "(" << r.x << "x" << r.y << ")";
    }

    friend ostream& operator<<(ostream& out, const PhysicsEditorJsonShape& r){
        return out << "Shape{" << r.name << ", " << r.imagePath << ", (" << r.origin.x << "x" << r.origin.y << "), " <<
            [&]{
                stringstream s;
                s << ", polygons [";
                for(auto const& i: r.polygons){
                    s << "[";
                    for(auto const& j: i){
                        s << "(" << j.x << "x" << j.y << "), ";
                    }
                    s << "]";
                }
                s << "]";
                return s.str();
            }() << [&]{
                stringstream s;
                s << ", circles [";
                for(auto const& i: r.circles) {
                    s << "{(" << i.center.x << "x" << i.center.y << "), " << i.radius << "}, ";
                }
                s << "]";
                return s.str();
            }();
    }
};

ComplexShape::ComplexShape() {
}

ComplexShape::ComplexShape(Image* image, File* file, const std::string& name, b2FixtureDef fixtureDef) :
    _fixtureDef(fixtureDef) {

    Ref<Image>{image};
    Ref<File>{file};

    jassert(image, "invalid image");
    jassert(file, "invalid file");
    jassert(!name.empty(), "invalid name");

    setlocale(LC_NUMERIC, "C"); // Чинит парсинг файла в некоторых случаях

    json j;
    file->getStream() >> j;

    float w = image->getWidth();
    float h = image->getHeight();

    for (auto const& rigidBody : j["rigidBodies"]) {
        PhysicsEditorJsonShape jsonShape{rigidBody};
        cout << jsonShape << endl;
    }

    for (auto const& rigidBody : j["rigidBodies"]) {
        if (rigidBody["name"] == name) {

            for (auto const& poligon : rigidBody["polygons"]) {
                vector<b2Vec2> poly;

                for (auto point : poligon)
                    poly.emplace_back(float(point["x"]) * w - w / 2, float(point["y"]) * h - h / 2);

                _polygons.push_back(poly);

                setScale(1, 1);
            }
            return;
        }
    }
    jassert(false, "no shape with name " + name);
}

void ComplexShape::get(nlohmann::json rigidBody) {

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

