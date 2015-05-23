/*
 * SpriteBox2d.h
 *
 *  Created on: 23 мая 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_SPRITEBOX2D_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_SPRITEBOX2D_H_

#ifdef SWIG
#else
#endif

#include "Box2dNode.h"
#include "Sprite.h"

namespace jupiter {

class NodeVisitor;
class Box2dVisitor;

class SpriteBox2d: public Sprite, public Box2dNode {
public:
    SpriteBox2d(Box2dVisitor*, float width, float height, BodyType = StaticBody);
    virtual ~SpriteBox2d();

    virtual SpriteBox2d* accept(NodeVisitor*);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_SPRITEBOX2D_H_ */
