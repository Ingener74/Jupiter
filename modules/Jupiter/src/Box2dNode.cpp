/*
 * Box2dNode.cpp
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#include <Box2D/Box2D.h>

#include "Jupiter/Box2DVisitor.h"
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

} /* namespace jupiter */
