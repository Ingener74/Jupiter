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
#endif

#include "JupiterBox2d.h"
#include "Node.h"

namespace jupiter {

class Image;
class Box2dVisitor;
class CollisionListener;
class NodeVisitor;

class Box2dNode: virtual public Node {
public:
    friend class Box2dVisitor;

    Box2dNode();
    Box2dNode(Box2dVisitor*, BodyDef, FixtureDef);
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

    Box2dNode* setBodyType(BodyType);
    BodyType getBodyType();

    Box2dNode* setLinearVelocity(b2Vec2 const& velocity);
    Vec3       getLinearVelocity() const;

    Box2dNode* setAngularVelocity(float angularVelocity);
    float getAngularVelocity() const;

    Box2dNode* applyTorque(float torque, bool wake);
    Box2dNode* applyLinearImpulse(b2Vec2 const& impulse, b2Vec2 const& point, bool wake);
    Box2dNode* applyAngularImpulse(float impulse, bool wake);
    Box2dNode* applyForce(b2Vec2 const& force, b2Vec2 const& point, bool wake);
    Box2dNode* applyForceToCenter(Vec2 const& force, bool wake);

    float getMass() const;
    float getInertia() const;

    float getLinearDamping() const;
    Box2dNode* setLinearDamping(float linearDamping);

    float getAngularDamping() const;
    Box2dNode* setAngularDamping(float angularDamping);

    float getGravityScale() const;
    Box2dNode* setGravityScale(float scale);

    b2BodyType getType() const;
    Box2dNode* setType(b2BodyType type);

    bool isBullet() const;
    Box2dNode* setBullet(bool flag);

    bool isSleepingAllowed() const;
    Box2dNode* setSleepingAllowed(bool flag);

    bool isAwake() const;
    Box2dNode* setAwake(bool flag);

    bool isActive() const;
    Box2dNode* setActive(bool flag);

    bool isFixedRotation() const;
    Box2dNode* setFixedRotation(bool flag);

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
