/*
 * Box2dNode.cpp
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#include "Jupiter/JupiterError.h"
#include "Jupiter/Image.h"
#include "Jupiter/CollisionListener.h"
#include "Jupiter/Box2dVisitor.h"
#include "Jupiter/PhysicsShape.h"
#include "Jupiter/Box2dNode.h"

namespace jupiter {

using namespace std;

Box2dNode::Box2dNode(): Node(){
}

Box2dNode::Box2dNode(Box2dVisitor* visitor, b2BodyDef bodyDef, PhysicsShape* shape) :
    _visitor(visitor) {

    _bodyDef              = bodyDef;
    _bodyDef.position.x   = _position.x;
    _bodyDef.position.y   = _position.y;
    _bodyDef.angle        = glm::angle(_rotation);
    _bodyDef.userData     = this;

    _shape                = shape;

    updateBody();
}

Box2dNode::~Box2dNode() {
    if (_body)
        _body->GetWorld()->DestroyBody(_body);
}

Box2dNode::Box2dNode(const Box2dNode& body){
    clone(const_cast<Box2dNode*>(&body));
}

Box2dNode* Box2dNode::clone(Box2dNode* node) {
    jassert(node, "node is invalid");
    *this = *node;

    _body    = nullptr;
    _fixtures.clear();

    updateBody();

    return this;
}

Box2dNode* Box2dNode::setRotation(float x, float y, float z, float angle) {
    Node::setRotation(x, y, z, angle);
    transform();
    return this;
}

Box2dNode* Box2dNode::rotate(float x, float y, float z, float angle) {
    Node::rotate(x, y, z, angle);
    transform();
    return this;
}

Box2dNode* Box2dNode::setPosition(float x, float y, float z) {
    Node::setPosition(x, y, z);
    transform();
    return this;
}

Box2dNode* Box2dNode::translate(float x, float y, float z) {
    Node::translate(x, y, z);
    transform();
    return this;
}

Box2dNode* Box2dNode::setScale(float x, float y, float z) {
    Node::setScale(x, y, z);
    updateFixtures();
    return this;
}

Box2dNode* Box2dNode::scale(float x, float y, float z) {
    Node::scale(x, y, z);
    updateFixtures();
    return this;
}

Box2dNode* Box2dNode::accept(NodeVisitor* nv) {
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

Box2dNode* Box2dNode::setPhysicsShape(PhysicsShape* shape) {
    jassert(shape, "invalid shape");
    _shape = shape;
    updateFixtures();
    return this;
}


PhysicsShape* Box2dNode::getPhysicsShape() {
    jassert(_shape, "no shape");
    return _shape;
}

b2Body* Box2dNode::getPhysicsBody() {
    jassert(_body, "no body");
    return _body;
}

b2Fixture* Box2dNode::getPhysicsFixture() {
    jassert(false, "deprecated");
}

CollisionListener* Box2dNode::getCollisionListener() {
    jassert(_collisionListener, "no listener");
    return _collisionListener;
}

Box2dNode* Box2dNode::setCollisionListener(CollisionListener* listener) {
    jassert(listener, "invalid listener");
    _collisionListener = listener;
    return this;
}

void Box2dNode::updateBody() {
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

void Box2dNode::updateFixtures() {
    jassert(_body, "no body");
    jassert(_shape, "no shape");

    for (auto i : _fixtures)
        _body->DestroyFixture(i);

    _shape->setScale(_scale.x, _scale.y);
    _fixtures.resize(_shape->shapesCount());

    for (size_t i = 0; i < _shape->shapesCount(); ++i)
        _fixtures.at(i) = _body->CreateFixture(_shape->getFixtureDef(i));
}

void Box2dNode::transform() {
    jassert(_body, "no body");
    jassert(_shape, "no shape");
    _body->SetTransform(b2Vec2(_position.x, _position.y), getRotationAngle());
}

} /* namespace jupiter */
