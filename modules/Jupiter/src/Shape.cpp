/*
 * Shape.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: pavel
 */

#include <iostream>

#include "Jupiter/Shape.h"

namespace jupiter {

using namespace std;

Shape::Shape(const std::vector<float>& data, Shape::Type type) :
        data(data), type(type) {
}

uint32_t Shape::getVertexCount() const {
    return vertexCount;
}

uint32_t Shape::getStride() const {
    return stride;
}

Shape::Type Shape::getType() const {
    return type;
}

const VertexComponent& Shape::getComponent(const std::string& name) {
    return components[name];
}

}
