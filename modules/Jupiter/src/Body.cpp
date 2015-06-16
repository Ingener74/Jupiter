/*
 * Box2dNode.cpp
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#include "Jupiter/JupiterError.h"
#include "Jupiter/Image.h"
#include "Jupiter/CollisionListener.h"
#include "Jupiter/Physics.h"
#include "Jupiter/PhysicsShape.h"
#include "Jupiter/Body.h"

namespace jupiter {

using namespace std;

Body::Body(): Node(){
}

Body::Body(Physics* visitor, b2BodyDef bodyDef, PhysicsShape* shape) :
    _visitor(visitor) {

    _bodyDef              = bodyDef;
    _bodyDef.position.x   = _position.x;
    _bodyDef.position.y   = _position.y;
    _bodyDef.angle        = glm::angle(_rotation);
    _bodyDef.userData     = this;

    _shape                = shape;

    updateBody();
}

Body::~Body() {
    if (_body)
        _body->GetWorld()->DestroyBody(_body);
}

Body::Body(const Body& body){
    clone(const_cast<Body*>(&body));
}

Body* Body::clone(Body* node) {
    Ref<Body>{node};

    jassert(node, "node is invalid");
    *this = *node;

    _body    = nullptr;
    _fixtures.clear();

    updateBody();

    return this;
}

Body* Body::setRotation(float x, float y, float z, float angle) {
    Node::setRotation(x, y, z, angle);
    transform();
    return this;
}

Body* Body::rotate(float x, float y, float z, float angle) {
    Node::rotate(x, y, z, angle);
    transform();
    return this;
}

Body* Body::setPosition(float x, float y, float z) {
    Node::setPosition(x, y, z);
    transform();
    return this;
}

Body* Body::translate(float x, float y, float z) {
    Node::translate(x, y, z);
    transform();
    return this;
}

Body* Body::setScale(float x, float y, float z) {
    Node::setScale(x, y, z);
    updateFixtures();
    return this;
}

Body* Body::scale(float x, float y, float z) {
    Node::scale(x, y, z);
    updateFixtures();
    return this;
}

Body* Body::accept(NodeVisitor* nv) {
    jassert(nv, "visitor is nullptr");
    if (_visible) {
        nv->push(this);
        nv->visit(this);
        for (auto i : _nodes) {
            jassert(i, "node is invalid");
            i->accept(nv);
        }
        nv->pop();
    }
    return this;
}

Body* Body::setPhysicsShape(PhysicsShape* shape) {
    jassert(shape, "invalid shape");
    _shape = shape;
    updateFixtures();
    return this;
}


PhysicsShape* Body::getPhysicsShape() {
    jassert(_shape, "no shape");
    return _shape.get();
}

b2Body* Body::getPhysicsBody() {
    jassert(_body, "no body");
    return _body;
}

b2Fixture* Body::getPhysicsFixture() {
    jassert(false, "deprecated");
}

CollisionListener* Body::getCollisionListener() {
    jassert(_collisionListener, "no listener");
    return _collisionListener.get();
}

Body* Body::setCollisionListener(CollisionListener* listener) {
    jassert(listener, "invalid listener");
    _collisionListener = listener;
    return this;
}

void Body::updateBody() {
    jassert(_visitor, "no visitor");

    if(_body)
        _visitor->getWorld()->DestroyBody(_body);

    _bodyDef.position.x = _position.x;
    _bodyDef.position.y = _position.y;
    _bodyDef.angle      = glm::angle(_rotation);
    _bodyDef.userData   = this;

    _body = _visitor->getWorld()->CreateBody(&_bodyDef);

    if (_shape)
        updateFixtures();
}

void Body::updateFixtures() {
    jassert(_body, "no body");
    jassert(_shape, "no shape");

    for (auto i : _fixtures)
        _body->DestroyFixture(i);

    _shape->setScale(_scale.x, _scale.y);
    _fixtures.resize(_shape->shapesCount());

    for (size_t i = 0; i < _shape->shapesCount(); ++i)
        _fixtures.at(i) = _body->CreateFixture(_shape->getFixtureDef(i));
}

void Body::transform() {
    jassert(_body, "no body");
    jassert(_shape, "no shape");
    _body->SetTransform(b2Vec2(_position.x, _position.y), getRotationAngle());
}

} /* namespace jupiter */
