/*
 * Physics.cpp
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#include <Box2D/Box2D.h>

#include "Jupiter/Settings.h"
#include "Jupiter/Game.h"
#include "Jupiter/Tools.h"
#include "Jupiter/Body.h"
#include "Jupiter/Node.h"
#include "Jupiter/CollisionListener.h"
#include "Jupiter/MoveListener.h"
#include "Jupiter/RotationListener.h"
#include "Jupiter/Transform.h"

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

class PrePhysics: public NodeVisitor {
public:
    virtual void push(Body*) {
    }
    virtual void visit(Body* body) {
        jassert(!_stack.empty(), "stack empty");
        auto transform = _stack.top();
        float len = body->distance(transform);
        if (len > MinDistance) {
            body->setPosition(transform);
        }
    }
    virtual void pop(Body*) {
    }

    virtual void push(Transform* t) {
        jassert(t, "invalid transform");
        _stack.push(t);
    }
    virtual void visit(Transform*) {
    }
    virtual void pop(Transform*) {
        _stack.pop();
    }

    stack<Transform*> _stack;
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

namespace  {

PrePhysics prePhysics;

}  // namespace

void Physics::begin() {

    getGame()->getRootNode()->accept(&prePhysics);

    _world->Step(_timeStep, _velocityIterations, _positionIterations);
}

void Physics::push(Body*) {
}

void Physics::pop(Body*) {
}

void Physics::visit(Body* body) {
    jassert(body, "node is empty");
    jassert(!_transforms.empty(), "no transform nodes");

    auto transform = _transforms.top();

    float x = body->_body->GetPosition().x;
    float y = body->_body->GetPosition().y;
    float z = transform->getPositionZ();

    float a = body->_body->GetAngle();

    transform->setPosition(x, y, z);
    transform->setRotationZ(a);
}

void Physics::push(Transform* transform) {
    jassert(transform, "invalid transform");
    _transforms.push(transform);
}

void Physics::visit(Transform*) {
}

void Physics::pop(Transform*) {
    _transforms.pop();
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
    jassert(a, "a body invalid");
    jassert(b, "b body invalid");
    if (a->_collisionListener)
        a->_collisionListener->collision(b);
    if (b->_collisionListener)
        b->_collisionListener->collision(a);
}

} /* namespace jupiter */
