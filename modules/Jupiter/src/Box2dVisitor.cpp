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
#include "Jupiter/Box2dVisitor.h"

namespace jupiter {

class ContactListener: public b2ContactListener {
public:
    ContactListener() {
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
        jassert(nodeA, "bad node A")

        auto nodeB = static_cast<Box2dNode*>(contact->GetFixtureB()->GetBody()->GetUserData());
        jassert(nodeB, "bad node B")

        nodeA->collision(nodeB);
        nodeB->collision(nodeA);
    }
};

Box2dVisitor::Box2dVisitor(float timeStep, int positionIterations, int velocityIterations) :
    _timeStep(timeStep), _positionIterations(positionIterations), _velocityIterations(velocityIterations) {

    b2Vec2 gravity(0, 9.8);

    _world = make_unique_<b2World>(gravity);

    _contactListener = make_unique_<ContactListener>();
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
    jassert(node, "node is empty")
    node->setPosition(node->getBox2dX(), node->getBox2dY(), node->getPositionZ());
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
    jassert(_world, "Box2D world is invalid")
    return _world.get();
}

Box2dVisitor* Box2dVisitor::setVelocityIterations(int velocityIterations) {
    _velocityIterations = velocityIterations;
    return this;
}

} /* namespace jupiter */

