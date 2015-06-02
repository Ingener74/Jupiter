/*
 * Box2dNode.h
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_BOX2DNODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_BOX2DNODE_H_

#ifdef SWIG
#else
    #include <Box2D/Box2D.h>
#endif

#include "Node.h"

namespace jupiter {

class Image;
class Box2dVisitor;
class CollisionListener;
class NodeVisitor;
class PhysicsShape;

class Box2dNode: virtual public Node {
public:
    friend class Box2dVisitor;

    Box2dNode();
    Box2dNode(Box2dVisitor*, b2BodyDef, b2FixtureDef);
    virtual ~Box2dNode();

    virtual Box2dNode* clone(Box2dNode*);

    virtual Box2dNode* setRotation(float x, float y, float z, float angle);
    virtual Box2dNode* rotate(float x, float y, float z, float angle);
    virtual Box2dNode* setPosition(float x, float y, float z);
    virtual Box2dNode* translate(float x, float y, float z);
    virtual Box2dNode* setScale(float x, float y, float z);
    virtual Box2dNode* scale(float x, float y, float z);

    virtual Box2dNode* accept(NodeVisitor*);

    Box2dNode* setPhysicsShape(Image*);
    Box2dNode* setPhysicsShape(PhysicsShape*);

    b2Body* getPhysicsBody();
    b2Fixture* getPhysicsFixture();

    CollisionListener* getCollisionListener();
    Box2dNode* setCollisionListener(CollisionListener*);

protected:
    Box2dVisitor*       _visitor            = nullptr;

    b2Body*             _body               = nullptr;
    b2Fixture*          _fixture            = nullptr;

    CollisionListener*  _collisionListener  = nullptr;

    float               _width              = 0.f;
    float               _height             = 0.f;

    b2BodyDef           _bodyDef;
    b2FixtureDef        _fixtureDef;

    Box2dNode(const Box2dNode&)             = default;
    Box2dNode& operator=(const Box2dNode&)  = default;

    void updateBody();
    void updateFixture();
    void transform();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_BOX2DNODE_H_ */
