/*
 * Box2DVisitor.cpp
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#include <Box2D/Box2D.h>

#include "Jupiter/Tools.h"
#include "Jupiter/Box2dNode.h"
#include "Jupiter/Node.h"
#include "Jupiter/CollisionListener.h"
#include "Jupiter/MoveListener.h"
#include "Jupiter/RotationListener.h"
#include "Jupiter/Box2dVisitor.h"

namespace jupiter {

using namespace std;
using namespace glm;

class ContactListener: public b2ContactListener {
public:
    ContactListener(Box2dVisitor* visitor) :
        _visitor(visitor) {
    }
    virtual ~ContactListener() {
    }

    virtual void BeginContact(b2Contact* contact) {
    }

    virtual void EndContact(b2Contact* contact) {
    }

    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    }

    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
        auto nodeA = static_cast<Box2dNode*>(contact->GetFixtureA()->GetBody()->GetUserData());
        jassert(nodeA, "bad node A");

        auto nodeB = static_cast<Box2dNode*>(contact->GetFixtureB()->GetBody()->GetUserData());
        jassert(nodeB, "bad node B");

        _visitor->collide(nodeA, nodeB);
    }

private:
    Box2dVisitor* _visitor = nullptr;
};

Box2dVisitor::Box2dVisitor(float timeStep, int positionIterations, int velocityIterations) :
    _timeStep(timeStep), _positionIterations(positionIterations), _velocityIterations(velocityIterations) {

    b2Vec2 gravity(0, -9.8);

    _world = make_unique_<b2World>(gravity);

    _contactListener = make_unique_<ContactListener>(this);
    _world->SetContactListener(_contactListener.get());
}

Box2dVisitor::~Box2dVisitor() {
}

void Box2dVisitor::begin() {
    _world->Step(_timeStep, _velocityIterations, _positionIterations);
}

void Box2dVisitor::push(Node*) {
}

void Box2dVisitor::pop() {
}

void Box2dVisitor::visit(Box2dNode* node) {
    jassert(node, "node is empty");
//    node->setPosition(node->_body->GetPosition().x, node->_body->GetPosition().y, node->_position.z);
//    node->setRotation(0.f, 0.f, 1.f, node->_body->GetAngle());

    float x = node->_body->GetPosition().x;
    float y = node->_body->GetPosition().y;
    float z = node->_position.z;
    float a = node->_body->GetAngle();

    node->_position.x = x;
    node->_position.y = y;
    node->_rotation = glm::rotate(quat { }, a, vec3 { 0.f, 0.f, 1.f });
    node->calcModel();
    if (node->_moveListener)
        node->_moveListener->move(x, y, z);
    if (node->_rotationListener)
        node->_rotationListener->rotate(0.f, 0.f, 1.f, a);
}

void Box2dVisitor::end() {
}

int Box2dVisitor::getPositionIterations() const {
    return _positionIterations;
}

Box2dVisitor* Box2dVisitor::setPositionIterations(int positionIterations) {
    _positionIterations = positionIterations;
    return this;
}

float Box2dVisitor::getTimeStep() const {
    return _timeStep;
}

Box2dVisitor* Box2dVisitor::setTimeStep(float timeStep) {
    _timeStep = timeStep;
    return this;
}

int Box2dVisitor::getVelocityIterations() const {
    return _velocityIterations;
}

b2World* Box2dVisitor::getWorld() {
    jassert(_world, "Box2D world is invalid");
    return _world.get();
}

Box2dVisitor* Box2dVisitor::setVelocityIterations(int velocityIterations) {
    _velocityIterations = velocityIterations;
    return this;
}

void Box2dVisitor::collide(Box2dNode* a, Box2dNode* b) {
    if (a->_collisionListener)
        a->_collisionListener->collision(b);
    if (b->_collisionListener)
        b->_collisionListener->collision(a);
}

} /* namespace jupiter */
