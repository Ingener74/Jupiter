/*
 * SpriteBox2d.cpp
 *
 *  Created on: 23 мая 2015 г.
 *      Author: Pavel
 */

#include "Jupiter/JupiterError.h"
#include "Jupiter/SpriteBox2d.h"

namespace jupiter {

SpriteBox2d::SpriteBox2d() :
    Sprite(), Box2dNode() {
}

SpriteBox2d::SpriteBox2d(Box2dVisitor* visitor, b2BodyDef bodyDef, PhysicsShape* shape) :
    Sprite(), Box2dNode(visitor, bodyDef, shape) {
}

SpriteBox2d::~SpriteBox2d() {
}

SpriteBox2d::SpriteBox2d(const SpriteBox2d& sprite){
    clone(const_cast<SpriteBox2d*>(&sprite));
}

SpriteBox2d* SpriteBox2d::clone(SpriteBox2d* node) {
    jassert(node, "node is invalid");
    *this = *node;
    Sprite::clone(node);
    Box2dNode::clone(node);
    return this;
}

SpriteBox2d* SpriteBox2d::accept(NodeVisitor* nv) {
    Box2dNode::accept(nv);
    Sprite::accept(nv);
    return this;
}

} /* namespace jupiter */

