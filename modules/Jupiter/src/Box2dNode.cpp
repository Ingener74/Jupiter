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

Box2dNode::Box2dNode(Box2dVisitor* v, float width, float height, BodyType bodyType): Node(), _visitor(v), _width(width), _height(height){
    b2BodyDef bodyDef;
    bodyDef.position.x = _position.x;
    bodyDef.position.y = _position.y;
    bodyDef.angle = glm::angle(_rotation);
    bodyDef.type = static_cast<b2BodyType>(bodyType);
    bodyDef.userData = this;

    _body = v->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width, height);

    _body->CreateFixture(&shape, 0.3f);
}

Box2dNode::~Box2dNode() {
}

Box2dNode* Box2dNode::clone(Box2dNode* node) {
    jassert(node, "node is invalid");
    *this = *node;
    jassert(false, "Нельзя просто так копировать физическое тело / not implemented body copy");
    return this;
}

Box2dNode* Box2dNode::setRotation(float x, float y, float z, float angle) {
    Node::setRotation(x, y, z, angle);
    _body->SetTransform(b2Vec2(_position.x, _position.y), getRotationAngle());
    return this;
}

Box2dNode* Box2dNode::rotate(float x, float y, float z, float angle) {
    Node::rotate(x, y, z, angle);
    _body->SetTransform(b2Vec2(_position.x, _position.y), getRotationAngle());
    return this;
}

Box2dNode* Box2dNode::setPosition(float x, float y, float z) {
    Node::setPosition(x, y, z);
    _body->SetTransform(b2Vec2(_position.x, _position.y), getRotationAngle());
    return this;
}

Box2dNode* Box2dNode::translate(float x, float y, float z) {
    Node::translate(x, y, z);
    _body->SetTransform(b2Vec2(_position.x, _position.y), getRotationAngle());
    return this;
}

Box2dNode* Box2dNode::setScale(float x, float y, float z) {
    Node::setScale(x, y, z);
    auto shape = dynamic_cast<b2PolygonShape*>(_body->GetFixtureList()->GetShape());
    shape->SetAsBox(_width * _scale.x, _height * _scale.y);
    return this;
}

Box2dNode* Box2dNode::scale(float x, float y, float z) {
    Node::scale(x, y, z);
    auto shape = dynamic_cast<b2PolygonShape*>(_body->GetFixtureList()->GetShape());
    shape->SetAsBox(_width * _scale.x, _height * _scale.y);
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

Box2dNode* Box2dNode::collision(Box2dNode* node) {
    if (_collisionListener)
        _collisionListener->collision(node);
    return this;
}

float Box2dNode::getBox2dX() const {
    return _body->GetPosition().x;
}

float Box2dNode::getBox2dY() const {
    return _body->GetPosition().y;
}

float Box2dNode::getBox2dAngle() const {
    return _body->GetAngle();
}

} /* namespace jupiter */

