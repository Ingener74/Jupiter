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

    virtual void BeginContact(b2Contact* contact) { B2_NOT_USED(contact); }

    /// Called when two fixtures cease to touch.
    virtual void EndContact(b2Contact* contact) { B2_NOT_USED(contact); }

    /// This is called after a contact is updated. This allows you to inspect a
    /// contact before it goes to the solver. If you are careful, you can modify the
    /// contact manifold (e.g. disable contact).
    /// A copy of the old manifold is provided so that you can detect changes.
    /// Note: this is called only for awake bodies.
    /// Note: this is called even when the number of contact points is zero.
    /// Note: this is not called for sensors.
    /// Note: if you set the number of contact points to zero, you will not
    /// get an EndContact callback. However, you may get a BeginContact callback
    /// the next step.
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
    {
        B2_NOT_USED(contact);
        B2_NOT_USED(oldManifold);
    }

    /// This lets you inspect a contact after the solver is finished. This is useful
    /// for inspecting impulses.
    /// Note: the contact manifold does not include time of impact impulses, which can be
    /// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
    /// in a separate data structure.
    /// Note: this is only called for contacts that are touching, solid, and awake.
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
    {
        B2_NOT_USED(contact);
        B2_NOT_USED(impulse);
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

    node->setPosition(0.f, 0.f, 0.f);
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

