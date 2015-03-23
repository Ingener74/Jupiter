/*
 * Shape.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: pavel
 */

#include "Jupiter/Shape.h"

namespace jupiter {

Shape::Shape(const std::vector<float>& data, Shape::Type type) :
        data(data), type(type) {
}

uint32_t Shape::getVertexCount() const {
    return data.size() / getStride();
}

uint32_t Shape::getStride() const {
    uint32_t sum = 0;
    for(const auto& i: components){
        sum += i.second.getSize();
    }
    return sum;
}

Shape::Type Shape::getType() const {
    return type;
}

const VertexComponent& Shape::getComponent(const std::string& name) {
    return components[name];
}

}
