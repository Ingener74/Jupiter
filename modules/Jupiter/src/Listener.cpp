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
    return _node ? _node : throw JupiterError("node is empty");
}

Listener* Listener::setNode(Node* node) {
    _node = node;
    return this;
}

} /* namespace jupiter */
