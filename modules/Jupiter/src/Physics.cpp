/*
 * Physics.cpp
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#include <Box2D/Box2D.h>

#include "Jupiter/Tools.h"
#include "Jupiter/Body.h"
#include "Jupiter/Node.h"
#include "Jupiter/CollisionListener.h"
#include "Jupiter/MoveListener.h"
#include "Jupiter/RotationListener.h"
#include "Jupiter/Physics.h"

namespace jupiter {

using namespace std;
using namespace glm;

class ContactListener: public b2ContactListener {
public:
    ContactListener(Physics* visitor) :
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
        auto nodeA = static_cast<Body*>(contact->GetFixtureA()->GetBody()->GetUserData());
        jassert(nodeA, "bad node A");

        auto nodeB = static_cast<Body*>(contact->GetFixtureB()->GetBody()->GetUserData());
        jassert(nodeB, "bad node B");

        _visitor->collide(nodeA, nodeB);
    }

private:
    Physics* _visitor = nullptr;
};

Physics::Physics(float timeStep, int positionIterations, int velocityIterations) :
    _timeStep(timeStep), _positionIterations(positionIterations), _velocityIterations(velocityIterations) {

    b2Vec2 gravity(0, -9.8);

    _world = make_unique_<b2World>(gravity);

    _contactListener = make_unique_<ContactListener>(this);
    _world->SetContactListener(_contactListener.get());
}

Physics::~Physics() {
}

void Physics::begin() {
    _world->Step(_timeStep, _velocityIterations, _positionIterations);
}

void Physics::push(Node*) {
}

void Physics::pop() {
}

void Physics::visit(Body* node) {
    jassert(node, "node is empty");

    float x = node->_body->GetPosition().x;
    float y = node->_body->GetPosition().y;
    float z = node->_position.z;
    float a = node->_body->GetAngle();

    node->_position.x = x;
    node->_position.y = y;
    node->_rotation = glm::rotate(quat { }, a, vec3 { 0.f, 0.f, 1.f });

    if (node->_moveListener)
        node->_moveListener->move(x, y, z);
    if (node->_rotationListener)
        node->_rotationListener->rotate(0.f, 0.f, 1.f, a);
}

void Physics::end() {
}

int Physics::getPositionIterations() const {
    return _positionIterations;
}

Physics* Physics::setPositionIterations(int positionIterations) {
    _positionIterations = positionIterations;
    return this;
}

float Physics::getTimeStep() const {
    return _timeStep;
}

Physics* Physics::setTimeStep(float timeStep) {
    _timeStep = timeStep;
    return this;
}

int Physics::getVelocityIterations() const {
    return _velocityIterations;
}

b2World* Physics::getWorld() {
    jassert(_world, "Box2D world is invalid");
    return _world.get();
}

Physics* Physics::setVelocityIterations(int velocityIterations) {
    _velocityIterations = velocityIterations;
    return this;
}

void Physics::collide(Body* a, Body* b) {
    if (a->_collisionListener)
        a->_collisionListener->collision(b);
    if (b->_collisionListener)
        b->_collisionListener->collision(a);
}

} /* namespace jupiter */
