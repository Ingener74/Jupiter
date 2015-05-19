/*
 * Listener.cpp
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#include "Jupiter/JupiterError.h"
#include "Jupiter/Listener.h"

namespace jupiter {

Listener::Listener() {
}

Listener::~Listener() {
}

Node* Listener::getNode() {
    jassert(_node, "node is empty");
    return _node;
}

Listener* Listener::setNode(Node* node) {
    _node = node;
    return this;
}

} /* namespace jupiter */
