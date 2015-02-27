/*
 * Node.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Jupiter/NodeVisitor.h"
#include "Jupiter/Node.h"

namespace jupiter
{

using namespace std;
using namespace glm;

Node::Node(const std::string& name): Object(name)
{
}

Node::~Node()
{
}

bool Node::NodePtr::operator <(const NodePtr& r) const
{
    return node->model[3].z < r.node->model[3].z || node < r.node;
}

bool Node::NodePtr::operator >(const NodePtr& r) const
{
    return node->model[3].z > r.node->model[3].z || node > r.node;
}

bool Node::NodePtr::operator ==(const NodePtr& r) const {
    return node == r.node;
}

bool Node::NodePtr::operator !=(const NodePtr& r) const {
    return node != r.node;
}

void Node::addNode(Node* node)
{
    if(!node)
        throw JupiterError("Node add nullptr node");
    nodes.insert(NodePtr{node});
}

set<Node::NodePtr>::iterator Node::begin()
{
    return nodes.begin();
}

set<Node::NodePtr>::iterator Node::end()
{
    return nodes.end();
}

float Node::getRotationX() const
{
    return 0.f;
}

float Node::getRotationY() const
{
    return 0.f;
}

float Node::getRotationZ() const
{
    return 0.f;
}

Node* Node::setRotation(float x, float y, float z)
{
    if(controller)
        controller->onRotate(x, y, z);
    return this;
}

Node* Node::setRotationX(float x)
{
    if (controller)
        controller->onRotate(x, 0, 0);
    return this;
}

Node* Node::setRotationY(float y)
{
    if (controller)
        controller->onRotate(0, y, 0);
    return this;
}

Node* Node::setRotationZ(float z)
{
    if (controller)
        controller->onRotate(0, 0, z);
    return this;
}

Node* Node::rotate(float x, float y, float z)
{
    if (controller)
        controller->onRotate(x, y, z);
    return this;
}

Node* Node::rotateX(float x)
{
    if (controller)
        controller->onRotate(x, 0, 0);
    return this;
}

Node* Node::rotateY(float y)
{
    if (controller)
        controller->onRotate(0, y, 0);
    return this;
}

Node* Node::rotateZ(float z)
{
    if (controller)
        controller->onRotate(0, 0, z);
    return this;
}

float Node::getPositionX() const
{
    return model[3].x;
}

float Node::getPositionY() const
{
    return model[3].y;
}

float Node::getPositionZ() const
{
    return model[3].z;
}

Node* Node::setPosition(float x, float y, float z)
{
    model[3].x = x;
    model[3].y = y;
    model[3].z = z;
    return this;
}

Node* Node::setPositionX(float x)
{
    model[3].x = x;
    return this;
}

Node* Node::setPositionY(float y)
{
    model[3].y = y;
    return this;
}

Node* Node::setPositionZ(float z)
{
    model[3].z = z;
    return this;
}

Node* Node::translate(float x, float y, float z)
{
    model = glm::translate(model, vec3{x, y, z});
    if (controller)
        controller->onMove(x, y, z);
    return this;
}

Node* Node::translateX(float x)
{
    model = glm::translate(model, vec3{x, 0.f, 0.f});
    if (controller)
        controller->onMove(x, 0, 0);
    return this;
}

Node* Node::translateY(float y)
{
    model = glm::translate(model, vec3{0.f, y, 0.f});
    if (controller)
        controller->onMove(0, y, 0);
    return this;
}

Node* Node::translateZ(float z)
{
    model = glm::translate(model, vec3{0.f, 0.f, z});
    if (controller)
        controller->onMove(0, 0, z);
    return this;
}

float Node::getScaleX() const
{
    return model[0].x;
}

float Node::getScaleY() const
{
    return model[1].y;
}

Node* Node::setScale(float x, float y)
{
    model[0].x = x;
    model[1].y = y;
    return this;
}

Node* Node::setScaleX(float x)
{
    model[0].x = x;
    return this;
}

Node* Node::setScaleY(float y)
{
    model[1].y = y;
    return this;
}

Node* Node::scale(float x, float y)
{
    model = glm::scale(model, vec3{x, y, 0.f});
    return this;
}

Node* Node::scaleX(float x)
{
    model = glm::scale(model, vec3{x, 0.f, 0.f});
    return this;
}

Node* Node::scaleY(float y)
{
    model = glm::scale(model, vec3{0.f, y, 0.f});
    return this;
}

bool Node::isVisible() const
{
    return visible;
}

Node* Node::setVisible(bool isVisible)
{
    visible = isVisible;
    if (controller)
        controller->onVisibleChanged(isVisible);
    return this;
}

Node* Node::accept(NodeVisitor* nv)
{
    if (!nv)
        throw JupiterError("Node: visitor is nullptr");
    nv->visit(this);
    return this;
}

Controller* Node::getController()
{
    return controller;
}

} /* namespace jupiter */

