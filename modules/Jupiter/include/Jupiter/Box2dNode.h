/*
 * Box2dNode.h
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_BOX2DNODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_BOX2DNODE_H_

#include "Node.h"

class b2Body;

namespace jupiter {

class Image;
class Box2dVisitor;
class CollisionListener;
class NodeVisitor;

class Box2dNode: virtual public Node {
public:
    Box2dNode(Box2dVisitor*, int width, int height);
    virtual ~Box2dNode();

    virtual Box2dNode* clone(Box2dNode*);

    virtual Box2dNode* setRotation(float x, float y, float z, float angle);
    virtual Box2dNode* rotate(float x, float y, float z, float angle);
    virtual Box2dNode* setPosition(float x, float y, float z);
    virtual Box2dNode* translate(float x, float y, float z);
    virtual Box2dNode* setScale(float x, float y, float z);
    virtual Box2dNode* scale(float x, float y, float z);

    virtual Box2dNode* accept(NodeVisitor*);

    Box2dNode* collision(Box2dNode*);

    float getBox2dX() const;
    float getBox2dY() const;
    float getBox2dAngle() const;

private:
    Box2dVisitor* _visitor = nullptr;
    b2Body* _body = nullptr;
    CollisionListener* _collisionListener = nullptr;

    Box2dNode(const Box2dNode&) = default;
    Box2dNode& operator=(const Box2dNode&) = default;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_BOX2DNODE_H_ */
