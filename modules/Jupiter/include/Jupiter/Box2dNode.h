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
class b2Fixture;

namespace jupiter {

class Image;
class Box2dVisitor;
class CollisionListener;
class NodeVisitor;

class Box2dNode: virtual public Node {
public:
    friend class Box2dVisitor;

    enum BodyType
    {
        StaticBody = 0,
        KinematicBody,
        DynamicBody
    };

    Box2dNode();
    Box2dNode(Box2dVisitor*, float width, float height, BodyType = StaticBody);
    virtual ~Box2dNode();

    virtual Box2dNode* clone(Box2dNode*);

    virtual Box2dNode* setRotation(float x, float y, float z, float angle);
    virtual Box2dNode* rotate(float x, float y, float z, float angle);
    virtual Box2dNode* setPosition(float x, float y, float z);
    virtual Box2dNode* translate(float x, float y, float z);
    virtual Box2dNode* setScale(float x, float y, float z);
    virtual Box2dNode* scale(float x, float y, float z);

    virtual Box2dNode* accept(NodeVisitor*);

    Box2dNode* setLinearVelocity(float x, float y);
    Box2dNode* setAngularVelocity(float angularVel);

    Box2dNode* applyForceToCenter(float x, float y, bool wake);

    CollisionListener* getCollisionListener();
    Box2dNode* setCollisionListener(CollisionListener*);

protected:
    b2Body*             _body               = nullptr;
    b2Fixture*          _fixture            = nullptr;
    CollisionListener*  _collisionListener  = nullptr;

    float               _width              = 0;
    float               _height             = 0;

    Box2dNode(const Box2dNode&)             = default;
    Box2dNode& operator=(const Box2dNode&)  = default;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_BOX2DNODE_H_ */
