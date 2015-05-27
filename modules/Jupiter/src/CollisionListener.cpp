/*
 * CollisionListener.cpp
 *
 *  Created on: May 15, 2015
 *      Author: pavel
 */

#include "Jupiter/Box2dNode.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/CollisionListener.h"

namespace jupiter {

CollisionListener::CollisionListener() {
}

CollisionListener::~CollisionListener() {
}

void CollisionListener::collision(Box2dNode*) {
}

Box2dNode* CollisionListener::getBox2dNode() {
    auto node = dynamic_cast<Box2dNode*>(Listener::getNode());
    jassert(node, "invalid cast");
    return node;
}

} /* namespace jupiter */
