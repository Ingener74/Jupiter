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
#include "Jupiter/Box2dNode.h"

namespace jupiter {

using namespace std;

Box2dNode::Box2dNode(): Node(){
}

Box2dNode::Box2dNode(Box2dVisitor* visitor, BodyDef bodyDef, FixtureDef fixtureDef) :
    _visitor(visitor) {
    _bodyDef.type               = static_cast<b2BodyType>(bodyDef.type);
    _bodyDef.angularVelocity    = bodyDef.angularVelocity;
    _bodyDef.linearDamping      = bodyDef.linearDamping  ;
    _bodyDef.angularDamping     = bodyDef.angularDamping ;
    _bodyDef.allowSleep         = bodyDef.allowSleep     ;
    _bodyDef.awake              = bodyDef.awake          ;
    _bodyDef.fixedRotation      = bodyDef.fixedRotation  ;
    _bodyDef.bullet             = bodyDef.bullet         ;
    _bodyDef.active             = bodyDef.active         ;
    _bodyDef.gravityScale       = bodyDef.gravityScale   ;

    _bodyDef.linearVelocity.x   = bodyDef.linearVelocity.x;
    _bodyDef.linearVelocity.y   = bodyDef.linearVelocity.y;

    _fixtureDef.friction        = fixtureDef.friction    ;
    _fixtureDef.restitution     = fixtureDef.restitution ;
    _fixtureDef.density         = fixtureDef.density     ;
    _fixtureDef.isSensor        = fixtureDef.isSensor    ;

    _bodyDef.position.x         = _position.x;
    _bodyDef.position.y         = _position.y;
    _bodyDef.angle              = glm::angle(_rotation);
    _bodyDef.userData           = this;

    updateBody();
}

Box2dNode::~Box2dNode() {
    if (_body)
        _body->GetWorld()->DestroyBody(_body);
}

Box2dNode* Box2dNode::clone(Box2dNode* node) {
    jassert(node, "node is invalid");
    *this = *node;

    _body    = nullptr;
    _fixture = nullptr;
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
    updateFixture();
    return this;
}

Box2dNode* Box2dNode::scale(float x, float y, float z) {
    Node::scale(x, y, z);
    updateFixture();
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

Box2dNode* Box2dNode::setPhysicsShape(Image* image) {
    jassert(image, "invalid image");
    _width  = _scale.x * (image->getWidth()  / 2);
    _height = _scale.y * (image->getHeight() / 2) ;
    updateFixture();
    return this;
}

Box2dNode* Box2dNode::setBodyType(BodyType bodyType) {
    _bodyDef.type = static_cast<b2BodyType>(bodyType);
    updateBody();
    return this;
}

BodyType Box2dNode::getBodyType() {
    return static_cast<BodyType>(_bodyDef.type);
}

Box2dNode* Box2dNode::setLinearVelocity(float x, float y) {
    jassert(_body && _fixture, "no body or no fixture");
    _body->SetLinearVelocity(b2Vec2(x, y));
    return this;
}

Box2dNode* Box2dNode::setAngularVelocity(float velocity) {
    jassert(_body && _fixture, "no body or no fixture");
    _body->SetAngularVelocity(velocity);
    return this;
}

Box2dNode* Box2dNode::applyForceToCenter(float x, float y, bool wake) {
    jassert(_body && _fixture, "no body or no fixture");
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

void Box2dNode::updateBody() {
    jassert(_visitor, "no visitor");

    if(_body)
        _visitor->getWorld()->DestroyBody(_body);

    _bodyDef.position.x = _position.x;
    _bodyDef.position.y = _position.y;
    _bodyDef.angle = glm::angle(_rotation);
    _bodyDef.userData = this;

    _body = _visitor->getWorld()->CreateBody(&_bodyDef);

    if (_width > 1e-6 && _height > 1e-6)
        updateFixture();
}

void Box2dNode::updateFixture() {
    jassert(_body, "no body");
    if(_fixture)
        _body->DestroyFixture(_fixture);

    b2PolygonShape shape;
    shape.SetAsBox(_width * _scale.x, _height * _scale.y);

    _fixtureDef.shape = &shape;
    _fixture = _body->CreateFixture(&_fixtureDef);
}

void Box2dNode::transform() {
    jassert(_body && _fixture, "no body or no fixture");
    _body->SetTransform(b2Vec2(_position.x, _position.y), getRotationAngle());
}

} /* namespace jupiter */

