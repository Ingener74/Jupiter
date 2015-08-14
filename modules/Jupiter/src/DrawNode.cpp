/*
 * DrawNode.cpp
 *
 *  Created on: Jul 7, 2015
 *      Author: pavel
 */

#include <Jupiter/DrawNode.h>

namespace jupiter {

DrawNode::DrawNode() {
}

DrawNode::~DrawNode() {
}

void DrawNode::bind(Shader* program) {
}

GLenum DrawNode::getMode() const {
    return 0;
}

size_t DrawNode::getCount() const {
    return 0;
}

} /* namespace jupiter */
