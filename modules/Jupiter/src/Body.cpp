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
#include "Jupiter/Transform.h"

#include "Jupiter/Body.h"

namespace jupiter {

using namespace std;
using namespace glm;
using namespace nlohmann;

Body::Body() :
    Node() {
}

Body::Body(Physics* visitor, b2BodyDef bodyDef, PhysicsShape* shape) :
    _visitor(visitor), _shape(shape), _bodyDef(bodyDef) {

    _bodyDef.userData = this;

    updateBody();
}

Body::~Body() {
    if (_body)
        _body->GetWorld()->DestroyBody(_body);
}

Body::Body(const Body& body) :
    Node(body) {
    *this = body;

    _body = nullptr;
    _fixtures.clear();

    updateBody();
}

Body* Body::clone() {
    return new Body(*this);
}

Body* Body::setParent(Node* node) {
    auto transform = dynamic_cast<Transform*>(node);
    jassert(transform, "parent must be transform");
    _body->SetTransform( { transform->getPositionX(), transform->getPositionY() }, transform->getRotationAngle());
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
        nv->pop(this);
    }
    return this;
}

json Body::getJson() const {
    return json{
        {
            "Body", {
                {"Base", {Node::getJson()}},
            }
        }
    };
}

ostream& operator<<(ostream& out, Body const& r){
    return out << setw(4) << r.getJson();
}

Body* Body::setPosition(Transform* transform) {
    jassert(transform, "invalid transform");
    jassert(_body, "no body");
    _body->SetTransform( { transform->getPositionX(), transform->getPositionY() }, transform->getRotationAngle());
    return this;
}

float Body::distance(Transform* transform) {
    jassert(transform, "invalid transform");
    jassert(_body, "no body");
    vec2 trans{transform->getPositionX(), transform->getPositionY()};
    vec2 body{_body->GetPosition().x, _body->GetPosition().y};
    return length(trans - body);
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

    // TODO масштаб???

    _fixtures.resize(_shape->shapesCount());

    for (size_t i = 0; i < _shape->shapesCount(); ++i)
        _fixtures.at(i) = _body->CreateFixture(_shape->getFixtureDef(i));
}

} /* namespace jupiter */

