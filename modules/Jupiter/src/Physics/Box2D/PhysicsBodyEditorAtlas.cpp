/*
 * PhysicsBodyEditorAtlas.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: pavel
 */

#include <sstream>

#include "Jupiter/Ref.h"
#include "Jupiter/File.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/PhysicsBodyEditorAtlas.h"

namespace jupiter {

using namespace std;
using namespace nlohmann;

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

ostream& operator <<(ostream& out, const b2Vec2& r) {
    return out << "(" << r.x << "x" << r.y << ")";
}

ostream& operator <<(ostream& out, const PhysicsBodyEditorShape& r) {

    json j{
        { "name", r.name },
        { "imagePath", r.imagePath },
        { "origin" , {
                {"x", r.origin.x},
                {"y", r.origin.y}
            }
        },
    };

    return out << j; /*"Shape{" << r.name << ", " << r.imagePath << ", (" << r.origin.x << "x" << r.origin.y << "), "
        << [&] {stringstream s;s << ", polygons [";for (const auto& i: r.polygons) {
                s << "[";
                for (const auto& j: i) {
                    s << "(" << j.x << "x" << j.y << "), ";
                }
                s << "]";
            }
            s << "]";
            return s.str();
        }() << [&] {
            stringstream s;
            s << ", circles [";
            for (const auto& i: r.circles) {
                s << "{(" << i.center.x << "x" << i.center.y << "), " << i.radius << "}, ";
            }
            s << "]";
            return s.str();
        }();*/
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

PhysicsBodyEditorShape PhysicsBodyEditorAtlas::getShape(const std::string& name) {
    auto it = _shapes.find(name);
    jassert(it != _shapes.end(), "no shape with name " + name);
    return it->second;
}

} /* namespace jupiter */

