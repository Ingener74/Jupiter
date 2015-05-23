/*
 * SpriteBox2d.cpp
 *
 *  Created on: 23 мая 2015 г.
 *      Author: Pavel
 */

#include "Jupiter/SpriteBox2d.h"

namespace jupiter {

SpriteBox2d::SpriteBox2d(Box2dVisitor* nv, float width, float height, BodyType bodyType) :
    Sprite(), Box2dNode(nv, width, height, bodyType) {
}

SpriteBox2d::~SpriteBox2d() {
}

SpriteBox2d* SpriteBox2d::accept(NodeVisitor* nv) {
    Box2dNode::accept(nv);
    Sprite::accept(nv);
    return this;
}

} /* namespace jupiter */
