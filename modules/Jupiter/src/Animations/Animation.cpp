/*
 * Animation.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: pavel
 */

#include "Jupiter/JupiterError.h"
#include "Jupiter/Animation.h"

namespace jupiter {

void Animation::setNode(Node* node) {
    jassert(node, "invalid node");
    _node = node;
}

Node* Animation::getNode() {
    jassert(_node, "no node");
    return _node;
}

} /* namespace jupiter */
