/*
 * VertexComponent.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ingener
 */

#include <Jupiter/VertexComponent.h>

namespace jupiter {

VertexComponent::VertexComponent(uint32_t size, float* offset) :
        size(size), offset(offset) {
    // Bind VBO
}

VertexComponent::~VertexComponent() {
    // Unbind VBO
}

uint32_t VertexComponent::getSize() const {
    return size;
}

const float* VertexComponent::getOffset() const {
    return offset;
}

} /* namespace jupiter */
