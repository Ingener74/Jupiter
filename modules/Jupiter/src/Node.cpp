/*
 * Node.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include <iostream>

#include "Jupiter/Controller.h"
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
    if (!node)
        throw JupiterError("Node add nullptr node");

    nodes.push_back(node);
    return this;
}

Node* Node::setParent(Node* parent) {
    Node::parent = parent;
    return this;
}

Node* Node::getParent() {
    return parent;
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
    if (controller)
        controller->onRotate(x, y, z);

    return this;
}

Node* Node::setRotationX(float x) {
    if (controller)
        controller->onRotate(x, 0, 0);

    return this;
}

Node* Node::setRotationY(float y) {
    if (controller)
        controller->onRotate(0, y, 0);

    return this;
}

Node* Node::setRotationZ(float z) {
    if (controller)
        controller->onRotate(0, 0, z);

    return this;
}

Node* Node::rotate(float x, float y, float z) {
    if (controller)
        controller->onRotate(x, y, z);

    return this;
}

Node* Node::rotateX(float angle) {
    model = glm::rotate(model, angle, glm::vec3(1.f, 0.f, 0.f));
    if (controller)
        controller->onRotate(angle, 0, 0);

    return this;
}

Node* Node::rotateY(float angle) {
    model = glm::rotate(model, angle, glm::vec3(0.f, 1.f, 0.f));
    if (controller)
        controller->onRotate(0, angle, 0);

    return this;
}

Node* Node::rotateZ(float angle) {
    model = glm::rotate(model, angle, glm::vec3(0.f, 0.f, 1.f));
    if (controller)
        controller->onRotate(0, 0, angle);

    return this;
}

float Node::getPositionX() const {
    return model[3].x;
}

float Node::getPositionY() const {
    return model[3].y;
}

float Node::getPositionZ() const {
    return model[3].z;
}

Node* Node::setPosition(float x, float y, float z) {
    model[3].x = x;
    model[3].y = y;
    model[3].z = z;
    if (controller)
        controller->onPositionChanged(x, y, z);

    return this;
}

Node* Node::setPositionX(float x) {
    model[3].x = x;
    if (controller)
        controller->onPositionChanged(x, 0.f, 0.f);

    return this;
}

Node* Node::setPositionY(float y) {
    model[3].y = y;
    if (controller)
        controller->onPositionChanged(0.f, y, 0.f);

    return this;
}

Node* Node::setPositionZ(float z) {
    model[3].z = z;
    if (controller)
        controller->onPositionChanged(0.f, 0.f, z);

    return this;
}

Node* Node::translate(float x, float y, float z) {
    model = glm::translate(model, glm::vec3 { x, y, z });
    if (controller)
        controller->onMove(x, y, z);

    return this;
}

Node* Node::translateX(float x) {
    model = glm::translate(model, glm::vec3 { x, 0.f, 0.f });
    if (controller)
        controller->onMove(x, 0, 0);

    return this;
}

Node* Node::translateY(float y) {
    model = glm::translate(model, glm::vec3 { 0.f, y, 0.f });
    if (controller)
        controller->onMove(0, y, 0);

    return this;
}

Node* Node::translateZ(float z) {
    model = glm::translate(model, glm::vec3 { 0.f, 0.f, z });
    if (controller)
        controller->onMove(0, 0, z);

    return this;
}

float Node::getScaleX() const {
    return model[0].x;
}

float Node::getScaleY() const {
    return model[1].y;
}

Node* Node::setScale(float x, float y) {
    model[0].x = x;
    model[1].y = y;
    return this;
}

Node* Node::setScaleX(float x) {
    model[0].x = x;
    return this;
}

Node* Node::setScaleY(float y) {
    model[1].y = y;
    return this;
}

Node* Node::scale(float x, float y) {
    model = glm::scale(model, glm::vec3 { x, y, 0.f });
    return this;
}

Node* Node::scaleX(float x) {
    model = glm::scale(model, glm::vec3 { x, 0.f, 0.f });
    return this;
}

Node* Node::scaleY(float y) {
    model = glm::scale(model, glm::vec3 { 0.f, y, 0.f });
    return this;
}

bool Node::isVisible() const {
    return visible;
}

Node* Node::setVisible(bool isVisible) {
    visible = isVisible;
    if (controller)
        controller->onVisibleChanged(isVisible);

    return this;
}

Node* Node::accept(NodeVisitor* nv) {
    if (!nv)
        throw JupiterError("Node: visitor is nullptr");

    if (visible) {

        nv->push(this);

        nv->visit(this);

        for (const auto& i : nodes) {
            i->accept(nv);
        }

        nv->pop();
    }

    return this;
}

Node* Node::setController(Controller* controller) {
    Node::controller = controller;
    return this;
}

Controller* Node::getController() {
    return controller;
}

const glm::mat4& Node::getModel() const {
    return model;
}

Node* jupiter::Node::setModel(const glm::mat4& model) {
    Node::model = model;
    return this;
}

} /* namespace jupiter */

