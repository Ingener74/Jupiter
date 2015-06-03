/*
 * ComplexShape.cpp
 *
 *  Created on: 03 июня 2015 г.
 *      Author: Pavel
 */

#include <vector>

//#include <json.hpp>

#include "Jupiter/JupiterError.h"
#include "Jupiter/ComplexShape.h"

namespace jupiter {

using namespace std;
using namespace nlohmann;

ComplexShape::ComplexShape() {
}

ComplexShape::ComplexShape(Image* image, File* file, const std::string& name, b2FixtureDef fixtureDef) {

//    json j;
//    file->getStream() >> j;
//
//    for(auto rigidBody: j["rigidBodies"]){
//        if(rigidBody["name"] == name){
//            float Ox = rigidBody["origin"]["x"];
//            float Oy = rigidBody["origin"]["y"];
//
//            for(auto poligon: rigidBody["polygons"]){
//
//                vector<b2Vec2> poly;
//
//                for(auto point: poligon){
//                    float x = point["x"];
//                    float y = point["y"];
//                    poly.emplace_back(x, y);
//                }
//
//                cout << "new poligon" << endl;
//            }
//        }
//    }
    jassert(false, "no shape in file");
}

ComplexShape::~ComplexShape() {
}

void ComplexShape::setScale(float x, float y) {
}

int ComplexShape::shapesCount() const {
}

b2FixtureDef* ComplexShape::getFixtureDef(int index) {
}

} /* namespace jupiter */
