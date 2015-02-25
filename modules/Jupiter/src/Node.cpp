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
    std::cout << __PRETTY_FUNCTION__ << "" << std::endl;
}

Node::~Node()
{
    std::cout << __PRETTY_FUNCTION__ << "" << std::endl;
    if (_controller)
        delete _controller;
    for (auto& i : _nodes)
        delete i.node;
}

bool Node::NodePtr::operator <(const NodePtr& r) const
{
    return node->_model[3].z < r.node->_model[3].z;
}

bool Node::NodePtr::operator >(const NodePtr& r) const
{
    return node->_model[3].z > r.node->_model[3].z;
}

void Node::addNode(Node* node)
{
    if(!node)
        throw JupiterError("Node add nullptr node");
    _nodes.insert(NodePtr{node});
}

set<Node::NodePtr>::iterator Node::begin()
{
    return _nodes.begin();
}

set<Node::NodePtr>::iterator Node::end()
{
    return _nodes.end();
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
    if(_controller)
        _controller->onRotate(x, y, z);
    return this;
}

Node* Node::setRotationX(float x)
{
    if (_controller)
        _controller->onRotate(x, 0, 0);
    return this;
}

Node* Node::setRotationY(float y)
{
    if (_controller)
        _controller->onRotate(0, y, 0);
    return this;
}

Node* Node::setRotationZ(float z)
{
    if (_controller)
        _controller->onRotate(0, 0, z);
    return this;
}

Node* Node::rotate(float x, float y, float z)
{
    if (_controller)
        _controller->onRotate(x, y, z);
    return this;
}

Node* Node::rotateX(float x)
{
    if (_controller)
        _controller->onRotate(x, 0, 0);
    return this;
}

Node* Node::rotateY(float y)
{
    if (_controller)
        _controller->onRotate(0, y, 0);
    return this;
}

Node* Node::rotateZ(float z)
{
    if (_controller)
        _controller->onRotate(0, 0, z);
    return this;
}

float Node::getPositionX() const
{
    return _model[3].x;
}

float Node::getPositionY() const
{
    return _model[3].y;
}

float Node::getPositionZ() const
{
    return _model[3].z;
}

Node* Node::setPosition(float x, float y, float z)
{
    _model[3].x = x;
    _model[3].y = y;
    _model[3].z = z;
    return this;
}

Node* Node::setPositionX(float x)
{
    _model[3].x = x;
    return this;
}

Node* Node::setPositionY(float y)
{
    _model[3].y = y;
    return this;
}

Node* Node::setPositionZ(float z)
{
    _model[3].z = z;
    return this;
}

Node* Node::translate(float x, float y, float z)
{
    _model = glm::translate(_model, vec3{x, y, z});
    if (_controller)
        _controller->onMove(x, y, z);
    return this;
}

Node* Node::translateX(float x)
{
    _model = glm::translate(_model, vec3{x, 0.f, 0.f});
    if (_controller)
        _controller->onMove(x, 0, 0);
    return this;
}

Node* Node::translateY(float y)
{
    _model = glm::translate(_model, vec3{0.f, y, 0.f});
    if (_controller)
        _controller->onMove(0, y, 0);
    return this;
}

Node* Node::translateZ(float z)
{
    _model = glm::translate(_model, vec3{0.f, 0.f, z});
    if (_controller)
        _controller->onMove(0, 0, z);
    return this;
}

float Node::getScaleX() const
{
    return _model[0].x;
}

float Node::getScaleY() const
{
    return _model[1].y;
}

Node* Node::setScale(float x, float y)
{
    _model[0].x = x;
    _model[1].y = y;
    return this;
}

Node* Node::setScaleX(float x)
{
    _model[0].x = x;
    return this;
}

Node* Node::setScaleY(float y)
{
    _model[1].y = y;
    return this;
}

Node* Node::scale(float x, float y)
{
    _model = glm::scale(_model, vec3{x, y, 0.f});
    return this;
}

Node* Node::scaleX(float x)
{
    _model = glm::scale(_model, vec3{x, 0.f, 0.f});
    return this;
}

Node* Node::scaleY(float y)
{
    _model = glm::scale(_model, vec3{0.f, y, 0.f});
    return this;
}

bool Node::isVisible() const
{
    return _isVisible;
}

Node* Node::setVisible(bool isVisible)
{
    _isVisible = isVisible;
    if (_controller)
        _controller->onVisibleChanged(isVisible);
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
    return _controller;
}

} /* namespace jupiter */

