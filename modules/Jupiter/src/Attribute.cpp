/*
 * Attribute.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

#include <iostream>
#include "Jupiter/Tools.h"
#include "Jupiter/Shape.h"
#include "Jupiter/Attribute.h"

namespace jupiter {

Attribute::Attribute(const std::string& name, int attribute) :
        name(name), attribute(attribute) {
    glEnableVertexAttribArray(attribute);
    CHECK_GL_ERROR
}

Attribute::~Attribute() {
    glDisableVertexAttribArray(attribute);
    CHECK_GL_ERROR
}

void Attribute::set(class Shape* shape) {
    auto component = shape->getComponent(name);
    glVertexAttribPointer(attribute, component.getSize(), GL_FLOAT, GL_FALSE, shape->getStride(),
            component.getOffset());
    CHECK_GL_ERROR
}

} /* namespace jupiter */
