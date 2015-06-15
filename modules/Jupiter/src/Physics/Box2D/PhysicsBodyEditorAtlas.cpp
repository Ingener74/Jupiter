/*
 * PhysicsBodyEditorAtlas.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: pavel
 */

#include <sstream>
#include <iomanip>

#include "Jupiter/Ref.h"
#include "Jupiter/File.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/PhysicsBodyEditorAtlas.h"

namespace jupiter {

using namespace std;
using namespace nlohmann;

ostream& operator <<(ostream& out, const b2Vec2& r) {
    return out << "(" << r.x << "x" << r.y << ")";
}

Circle::Circle(b2Vec2 center, float radius) :
    center(center), radius(radius) {
}

PhysicsBodyEditorShape::PhysicsBodyEditorShape(json rigidBody) {
    string n = rigidBody["name"];
    string ip = rigidBody["imagePath"];
    name = n;
    imagePath = ip;
    origin.x = rigidBody["origin"]["x"];
    origin.y = rigidBody["origin"]["y"];
    for (const auto& polygon : rigidBody["polygons"]) {
        vector<b2Vec2> poly;
        for (auto point : polygon)
            poly.emplace_back(float(point["x"]), float(point["y"]));
        polygons.push_back(poly);
    }
    for (const auto& circle : rigidBody["circles"])
        circles.emplace_back(b2Vec2 { float(circle["cx"]), float(circle["cy"]) }, float(circle["r"]));
}

json PhysicsBodyEditorShape::getJson() const {
    return json{
        { "name", name },
        { "imagePath", imagePath },
        { "origin" , {
                {"x", origin.x},
                {"y", origin.y}
            }
        },
        { "polygons", [=]{
            json j;
            for(auto const& poly: polygons){
                json polygon;
                for(auto const& point: poly)
                    polygon.push_back(json { {"x", point.x}, {"y", point.y}});
                j.push_back(polygon);
            }
            return j;
        }()},
        { "circles", [=]{
            json circles_;
            for(auto const& circle: circles)
                circles_.push_back(json { {"cx", circle.center.x}, {"cy", circle.center.y}, {"cx", circle.radius}});
            return circles_;
        }()},
    };
}

ostream& operator <<(ostream& out, const PhysicsBodyEditorShape& r) {
    return out << setw(4) << r.getJson();
}

PhysicsBodyEditorAtlas::PhysicsBodyEditorAtlas(File* atlas) {
    Ref<File> { atlas };
    jassert(atlas, "invalid file");

    setlocale(LC_NUMERIC, "C"); // Чинит парсинг файла в некоторых случаях

    json j;
    atlas->getStream() >> j;

    for (auto const& rigidBody : j["rigidBodies"]) {
        PhysicsBodyEditorShape shape { rigidBody };
        _shapes[shape.name] = shape;
    }
}

PhysicsBodyEditorAtlas::~PhysicsBodyEditorAtlas() {
}

PhysicsBodyEditorShape PhysicsBodyEditorAtlas::getShape(const string& name) {
    auto it = _shapes.find(name);
    jassert(it != _shapes.end(), "no shape with name " + name);
    return it->second;
}

json PhysicsBodyEditorAtlas::getJson() const {
    return json { "rigidBodies", [=] {
        json rigidBodies;
        for(auto const& i: _shapes)
            rigidBodies.push_back(i.second.getJson());
        return rigidBodies;
    }() };
}

ostream& operator<<(ostream& out, const PhysicsBodyEditorAtlas& r) {
    return out << setw(4) << r.getJson();
}

} /* namespace jupiter */

