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
#include "Jupiter/Box2DVisitor.h"

namespace jupiter {

Box2DVisitor::Box2DVisitor(float timeStep, int32 positionIterations, int32 velocityIterations) :
    _timeStep(timeStep), _positionIterations(positionIterations), _velocityIterations(velocityIterations) {

    b2Vec2 gravity(0, 9.8);

    _world = make_unique_<b2World>(gravity);
}

Box2DVisitor::~Box2DVisitor() {
}

void Box2DVisitor::begin() {
    _world->Step(_timeStep, _velocityIterations, _positionIterations);
}

void Box2DVisitor::push(Node*) {
}

void Box2DVisitor::pop() {
}

void Box2DVisitor::visit(Box2dNode* node) {
    jassert(node, "node is empty")

    node->setPosition(0.f, 0.f, 0.f);
}

void Box2DVisitor::end() {
}

int32 Box2DVisitor::getPositionIterations() const {
    return _positionIterations;
}

Box2DVisitor* Box2DVisitor::setPositionIterations(int32 positionIterations) {
    _positionIterations = positionIterations;
    return this;
}

float Box2DVisitor::getTimeStep() const {
    return _timeStep;
}

Box2DVisitor* Box2DVisitor::setTimeStep(float timeStep) {
    _timeStep = timeStep;
    return this;
}

int32 Box2DVisitor::getVelocityIterations() const {
    return _velocityIterations;
}

b2World* Box2DVisitor::getWorld() {
    jassert(_world, "Box2D world is invalid")
    return _world.get();
}

Box2DVisitor* Box2DVisitor::setVelocityIterations(int32 velocityIterations) {
    _velocityIterations = velocityIterations;
    return this;
}

} /* namespace jupiter */

