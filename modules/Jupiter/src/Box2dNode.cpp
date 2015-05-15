/*
 * Box2dNode.cpp
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#include <Box2D/Box2D.h>

#include "Jupiter/Box2dVisitor.h"
#include "Jupiter/Box2dNode.h"

namespace jupiter {

Box2dNode::Box2dNode(Box2dVisitor* v) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(getPositionX(), getPositionY());

    _body = v->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(100, 100);

    _body->CreateFixture(&box, 0.3f);
}

Box2dNode::~Box2dNode() {
}

Box2dNode* Box2dNode::setPosition(float x, float y, float z) {
    Node::setPosition(x, y, z);
    _body->SetTransform(b2Vec2(getPositionX(), getPositionY()), getRotationZ());
    return this;
}

Box2dNode* Box2dNode::translate(float x, float y, float z) {
    Node::translate(x, y, z);
    _body->SetTransform(b2Vec2(getPositionX(), getPositionY()), getRotationZ());
    return this;
}

} /* namespace jupiter */
