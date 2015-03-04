/*
 * Node.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include <iostream>

#include "Jupiter/NodeVisitor.h"
#include "Jupiter/Node.h"

namespace jupiter {

using namespace std;
using namespace glm;

Node* Node::accept(NodeVisitor* nv) {
    if (!nv)
        throw JupiterError("Node: visitor is nullptr");

    nv->visit(this);
    return this;
}

} /* namespace jupiter */

