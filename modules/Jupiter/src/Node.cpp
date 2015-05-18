/*
 * Node.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include <iostream>

#include "Jupiter/Controller.h"
#include "Jupiter/MoveListener.h"
#include "Jupiter/ScaleListener.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/NodeVisitor.h"
#include "Jupiter/Node.h"

namespace jupiter {

using namespace std;
using namespace glm;

Node::Node() {
}

Node::~Node() {
}

Node* Node::addNode(Node* node) {
    jassert(node, "Node add nullptr node");
    _nodes.push_back(node->setParent(this));
    return this;
}

Node* Node::setParent(Node* parent) {
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

Node* Node::setRotation(float x, float y, float z) {
    if (_controller)
        _controller->onRotate(x, y, z);

    return this;
}

Node* Node::setRotationX(float x) {
    if (_controller)
        _controller->onRotate(x, 0, 0);

    return this;
}

Node* Node::setRotationY(float y) {
    if (_controller)
        _controller->onRotate(0, y, 0);

    return this;
}

Node* Node::setRotationZ(float z) {
    if (_controller)
        _controller->onRotate(0, 0, z);

    return this;
}

Node* Node::rotate(float x, float y, float z) {
    if (_controller)
        _controller->onRotate(x, y, z);

    return this;
}

Node* Node::rotateX(float angle) {
    _model = glm::rotate(_model, angle, glm::vec3(1.f, 0.f, 0.f));
    if (_controller)
        _controller->onRotate(angle, 0, 0);

    return this;
}

Node* Node::rotateY(float angle) {
    _model = glm::rotate(_model, angle, glm::vec3(0.f, 1.f, 0.f));
    if (_controller)
        _controller->onRotate(0, angle, 0);

    return this;
}

Node* Node::rotateZ(float angle) {
    _model = glm::rotate(_model, angle, glm::vec3(0.f, 0.f, 1.f));
    if (_controller)
        _controller->onRotate(0, 0, angle);

    return this;
}

float Node::getPositionX() const {
    return _model[3].x;
}

float Node::getPositionY() const {
    return _model[3].y;
}

float Node::getPositionZ() const {
    return _model[3].z;
}

Node* Node::setPosition(float x, float y, float z) {
    _model[3].x = x;
    _model[3].y = y;
    _model[3].z = z;
    if (_controller)
        _controller->onPositionChanged(x, y, z);
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
    _model = glm::translate(_model, glm::vec3 { x, y, z });
    if (_controller)
        _controller->onMove(x, y, z);
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
    return _model[0].x;
}

float Node::getScaleY() const {
    return _model[1].y;
}

float Node::getScaleZ() const {
    return _model[2].z;
}

Node* Node::setScale(float x, float y, float z) {
    _model[0].x = x;
    _model[1].y = y;
    _model[2].z = z;
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
    _model = glm::scale(_model, glm::vec3 { x, y, z });
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
    if (_controller)
        _controller->onVisibleChanged(isVisible);

    return this;
}

Node* Node::accept(NodeVisitor* nv) {
    jassert(nv, "Node: visitor is nullptr");

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

Node* Node::setController(Controller* controller) {
    Node::_controller = controller;
    return this;
}

Controller* Node::getController() {
    return _controller;
}

Node* Node::setMoveListener(MoveListener* moveListener) {
    _moveListener = moveListener;
    _moveListener->setNode(this);
    return this;
}

MoveListener* Node::getMoveListener() {
    jassert(_moveListener, "no move listener")
    return _moveListener;
}

const glm::mat4& Node::getModel() const {
    return _model;
}

Node* Node::setModel(const glm::mat4& model) {
    jassert(false, "deprecated")
//    Node::_model = model;
    return this;
}

ScaleListener* Node::getScaleListener() {
    jassert(_scaleListener, "no scale listener")
    return _scaleListener;
}

Node* Node::setScaleListener(ScaleListener* scaleListener) {
    _scaleListener = scaleListener;
    return this;
}

} /* namespace jupiter */
