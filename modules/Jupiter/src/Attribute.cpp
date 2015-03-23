/*
 * Attribute.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

#include "Jupiter/Shape.h"
#include "Jupiter/Attribute.h"

namespace jupiter {

Attribute::Attribute(const std::string& name, int attribute) :
        name(name), attribute(attribute) {
    glEnableVertexAttribArray(attribute);
}

Attribute::~Attribute() {
    glDisableVertexAttribArray(attribute);
}

void Attribute::set(class Shape* shape) {
    auto component = shape->getComponent(name);
    glVertexAttribPointer(attribute, component.getSize(), GL_FLOAT, GL_FALSE, shape->getStride(),
            component.getOffset());
}

} /* namespace jupiter */
