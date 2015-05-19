/*
 * Node.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Jupiter/MoveListener.h"
#include "Jupiter/ScaleListener.h"
#include "Jupiter/RotationListener.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/NodeVisitor.h"
#include "Jupiter/Tools.h"
#include "Jupiter/Node.h"

namespace jupiter {

using namespace std;
using namespace glm;

Node::Node() {
}

Node::~Node() {
}

Node* Node::addNode(Node* node) {
    jassert(node, "node is nullptr")
    _nodes.push_back(node->setParent(this));
    return this;
}

Node* Node::removeNode(Node* node) {
    jassert(node, "node is nullptr")
    _nodes.remove(node);
    return this;
}

Node* Node::setParent(Node* parent) {
    jassert(parent, "parent is nullptr")
    Node::_parent = parent;
    return this;
}

Node* Node::getParent() {
    return _parent;
}

float Node::getRotationX() const {
    return 0.f;
}

float Node::getRotationY() const {
    return 0.f;
}

float Node::getRotationZ() const {
    return 0.f;
}

Node* Node::setRotation(float x, float y, float z, float angle) {
    _rotation.x = x;
    _rotation.y = y;
    _rotation.z = z;
    _rotation.w = angle;
    calcModel();
    if (_rotationListener)
        _rotationListener->rotate(x, y, z, angle);
    return this;
}

Node* Node::setRotationX(float angle) {
    return setRotation(1.f, 0.f, 0.f, angle);
}

Node* Node::setRotationY(float angle) {
    return setRotation(0.f, 1.f, 0.f, angle);
}

Node* Node::setRotationZ(float angle) {
    return setRotation(0.f, 0.f, 1.f, angle);
}

Node* Node::rotate(float x, float y, float z, float angle) {
    _rotation.x = x;
    _rotation.y = y;
    _rotation.z = z;
    _rotation.w = angle;
    calcModel();
    if (_rotationListener)
        _rotationListener->rotate(x, y, z, angle);
    return this;
}

Node* Node::rotateX(float angle) {
    return rotate(1.f, 0.f, 0.f, angle);
}

Node* Node::rotateY(float angle) {
    return rotate(0.f, 1.f, 0.f, angle);
}

Node* Node::rotateZ(float angle) {
    return rotate(0.f, 0.f, 1.f, angle);
}

float Node::getPositionX() const {
    return _position.x;
}

float Node::getPositionY() const {
    return _position.y;
}

float Node::getPositionZ() const {
    return _position.z;
}

Node* Node::setPosition(float x, float y, float z) {
    _position.x = x;
    _position.y = y;
    _position.z = z;
    calcModel();
    if (_moveListener)
        _moveListener->move(x, y, z);
    return this;
}

Node* Node::setPositionX(float x) {
    return setPosition(x, 0.f, 0.f);
}

Node* Node::setPositionY(float y) {
    return setPosition(0.f, y, 0.f);
}

Node* Node::setPositionZ(float z) {
    return setPosition(0.f, 0.f, z);
}

Node* Node::translate(float x, float y, float z) {
    _position.x += x;
    _position.y += y;
    _position.z += z;
    calcModel();
    if (_moveListener)
        _moveListener->move(getPositionX(), getPositionY(), getPositionZ());
    return this;
}

Node* Node::translateX(float x) {
    return translate(x, 0.f, 0.f);
}

Node* Node::translateY(float y) {
    return translate(0.f, y, 0.f);
}

Node* Node::translateZ(float z) {
    return translate(0.f, 0.f, z);
}

float Node::getScaleX() const {
    return _scale.x;
}

float Node::getScaleY() const {
    return _scale.y;
}

float Node::getScaleZ() const {
    return _scale.z;
}

Node* Node::setScale(float x, float y, float z) {
    _scale.x = x;
    _scale.y = y;
    _scale.z = z;
    calcModel();
    if (_scaleListener)
        _scaleListener->scale(x, y, z);
    return this;
}

Node* Node::setScale(float scale) {
    return setScale(scale, scale, scale);
}

Node* Node::setScaleX(float x) {
    return setScale(x, 0.f, 0.f);
}

Node* Node::setScaleY(float y) {
    return setScale(0.f, y, 0.f);
}

Node* Node::setScaleZ(float z) {
    return setScale(0.f, 0.f, z);
}

Node* Node::scale(float x, float y, float z) {
    _scale.x *= x;
    _scale.y *= y;
    _scale.z *= z;
    calcModel();
    if (_scaleListener)
        _scaleListener->scale(x, y, z);
    return this;
}

Node* Node::scale(float s) {
    return scale(s, s, s);
}

Node* Node::scaleX(float x) {
    return scale(x, 0.f, 0.f);
}

Node* Node::scaleY(float y) {
    return scale(0.f, y, 0.f);
}

Node* Node::scaleZ(float z) {
    return scale(0.f, 0.f, z);
}

bool Node::isVisible() const {
    return _visible;
}

Node* Node::setVisible(bool isVisible) {
    _visible = isVisible;
    return this;
}

Node* Node::accept(NodeVisitor* nv) {
    jassert(nv, "visitor is nullptr");

    if (_visible) {

        nv->push(this);

        nv->visit(this);

        for (auto i : _nodes) {
            i->accept(nv);
        }

        nv->pop();
    }

    return this;
}

Node* Node::setMoveListener(MoveListener* moveListener) {
    jassert(moveListener, "move listener is nullptr")
    _moveListener = moveListener;
    _moveListener->setNode(this);
    return this;
}

MoveListener* Node::getMoveListener() {
    jassert(_moveListener, "no move listener")
    return _moveListener;
}

Node* Node::setScaleListener(ScaleListener* listener) {
    jassert(listener, "scale listener is nullptr")
    _scaleListener = listener;
    _scaleListener->setNode(this);
    return this;
}

ScaleListener* Node::getScaleListener() {
    jassert(_scaleListener, "no scale listener")
    return _scaleListener;
}

Node* Node::setRotationListener(RotationListener* listener) {
    jassert(listener, "rotation listener is nullptr")
    _rotationListener = listener;
    _rotationListener->setNode(this);
    return this;
}

RotationListener* Node::getRotationListener() {
    jassert(_rotationListener, "rotation listener is nullptr")
    return _rotationListener;
}

const glm::mat4& Node::getModel() const {
    return _model;
}

Node* Node::setModel(const glm::mat4& model) {
    jassert(false, "deprecated")
//    _model = model;
    return this;
}

void Node::calcModel() {
//    auto rotation = ;
//    cout << _rotation.x << " " << _rotation.y << " " << _rotation.z << " " << _rotation.w << " " << endl;
//    cout << rotation << endl;
    _model = glm::translate({}, _position) * glm::mat4_cast(_rotation) *  glm::scale({}, _scale);
}

} /* namespace jupiter */

