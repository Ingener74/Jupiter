/*
 * Box2dNode.cpp
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#include <Box2D/Box2D.h>

#include "Jupiter/JupiterError.h"
#include "Jupiter/Image.h"
#include "Jupiter/CollisionListener.h"
#include "Jupiter/Box2dVisitor.h"
#include "Jupiter/Box2dNode.h"

namespace jupiter {

using namespace std;

Box2dNode::Box2dNode(): Node(){
}

Box2dNode::Box2dNode(Box2dVisitor* v, float width, float height, BodyType bodyType): Node(), _width(width), _height(height){
    b2BodyDef bodyDef;
    bodyDef.position.x = _position.x;
    bodyDef.position.y = _position.y;
    bodyDef.angle = glm::angle(_rotation);
    bodyDef.type = static_cast<b2BodyType>(bodyType);
    bodyDef.userData = this;

    _body = v->getWorld()->CreateBody(&bodyDef);

    reshape();
}

Box2dNode::~Box2dNode() {
    if (_body)
        _body->GetWorld()->DestroyBody(_body);
}

Box2dNode* Box2dNode::clone(Box2dNode* node) {
    jassert(node, "node is invalid");
    *this = *node;

    b2BodyDef bd;
    bd.position.x = node->_body->GetPosition().x;
    bd.position.y = node->_body->GetPosition().y;
    bd.angle      = node->_body->GetAngle();
    bd.type       = node->_body->GetType();
    bd.userData   = this;

    _body = node->_body->GetWorld()->CreateBody(&bd);
    jassert(_body, "create body error");

    b2PolygonShape shape;
    shape.SetAsBox(node->_width, node->_height);

    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = node->_body->GetFixtureList()->GetDensity();
    fd.friction = node->_body->GetFixtureList()->GetFriction();

    _body->CreateFixture(&fd);

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
    reshape();
    return this;
}

Box2dNode* Box2dNode::scale(float x, float y, float z) {
    Node::scale(x, y, z);
    reshape();
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

Box2dNode* Box2dNode::setLinearVelocity(float x, float y) {
    jassert(_body, "no body");
    _body->SetLinearVelocity(b2Vec2(x, y));
    return this;
}

Box2dNode* Box2dNode::setAngularVelocity(float velocity) {
    jassert(_body, "no body");
    _body->SetAngularVelocity(velocity);
    return this;
}

Box2dNode* Box2dNode::applyForceToCenter(float x, float y, bool wake) {
    _body->ApplyForceToCenter( { x, y }, wake);
    return this;
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

void Box2dNode::reshape() {
    jassert(_body, "no body");
    if(_fixture)
        _body->DestroyFixture(_fixture);

    b2PolygonShape shape;
    shape.SetAsBox(_width * _scale.x, _height * _scale.y);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density  = 3.f;
    fixtureDef.friction = .3f;
    fixtureDef.restitution = .4f;

    _fixture = _body->CreateFixture(&fixtureDef);
}

void Box2dNode::transform() {
    jassert(_body, "no body");
    _body->SetTransform(b2Vec2(_position.x, _position.y), getRotationAngle());
}

} /* namespace jupiter */

