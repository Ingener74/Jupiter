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
using namespace glm;

Shape::Shape(const std::vector<float>& data, Shape::Type type) :
        data(data), type(type) {
}

uint32_t Shape::getVertexCount() const {
    uint32_t sum = 0;
    for(const auto& i: components){
        sum += i.second.getSize();
    }
    return data.size() / sum;
}

uint32_t Shape::getStride() const {
    uint32_t sum = 0;
    for(const auto& i: components){
        sum += i.second.getSize();
    }
    return sum * sizeof(float);
}

Shape::Type Shape::getType() const {
    return type;
}

const VertexComponent& Shape::getComponent(const std::string& name) {
    return components[name];
}

void jupiter::Shape::test(const glm::mat4& mvp) {

    for(int i = 0; i < getVertexCount(); ++i){

        int j = getStride() * i;

        vec4 in{data[j], data[j + 1], data[j + 2], 1};

        vec4 out = mvp * in;

        cout << out.x << " " << out.y << " " << out.z << " " << out.w << endl;
    }
}

}
