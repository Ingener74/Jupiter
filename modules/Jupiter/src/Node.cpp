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

int Node::leakCheck = 0;

Node::~Node() {
    for (auto i : nodes)
        if (i.created)
            delete i.node;

    --leakCheck;
}

Node* Node::accept(NodeVisitor* nv) {
    if (!nv)
        throw JupiterError("Node: visitor is nullptr");

    if (visible) {
        nv->visit(this);

        for (const auto& i : nodes) {
            i.node->accept(nv);
        }
    }

    return this;
}

} /* namespace jupiter */

