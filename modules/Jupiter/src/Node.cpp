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

#include <Jupiter/Builder.h>

#include <Jupiter/NodeVisitor.h>
#include <Jupiter/NodeImpl.h>
#include <Jupiter/Node.h>

namespace jupiter
{

using namespace std;
using namespace glm;

Node::Node()
{
}

Node::Node(const string& node): _impl(Builder<Node, NodeImpl>::create(node))
{
}

Node::~Node()
{
}

bool Node::operator <(const Node& r)
{
    return _impl->getModel()[3].z < r._impl->getModel()[3].z;
}

bool Node::operator >(const Node& r)
{
    return _impl->getModel()[3].z > r._impl->getModel()[3].z;
}

Node& Node::operator [](const std::string& nodeName)
{
    return _impl->getNodes()[nodeName];
}

void Node::addNode(const std::string& name, Node node)
{
    _impl->getNodes()[name] = node;
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

Node& Node::setRotation(float x, float y, float z)
{
    _impl->getController().onRotate(x, y, z);
    return *this;
}

Node& Node::setRotationX(float x)
{
    _impl->getController().onRotate(x, 0, 0);
    return *this;
}

Node& Node::setRotationY(float y)
{
    _impl->getController().onRotate(0, y, 0);
    return *this;
}

Node& Node::setRotationZ(float z)
{
    _impl->getController().onRotate(0, 0, z);
    return *this;
}

Node& Node::rotate(float x, float y, float z)
{
    _impl->getController().onRotate(x, y, z);
    return *this;
}

Node& Node::rotateX(float x)
{
    _impl->getController().onRotate(x, 0, 0);
    return *this;
}

Node& Node::rotateY(float y)
{
    _impl->getController().onRotate(0, y, 0);
    return *this;
}

Node& Node::rotateZ(float z)
{
    _impl->getController().onRotate(0, 0, z);
    return *this;
}

float Node::getPositionX() const
{
    return _impl->getModel()[3].x;
}

float Node::getPositionY() const
{
    return _impl->getModel()[3].y;
}

float Node::getPositionZ() const
{
    return _impl->getModel()[3].z;
}

Node& Node::setPosition(float x, float y, float z)
{
    auto m = _impl->getModel();
    m[3].x = x;
    m[3].y = y;
    m[3].z = z;
    _impl->setModel(m);
    return *this;
}

Node& Node::setPositionX(float x)
{
    auto m = _impl->getModel();
    m[3].x = x;
    _impl->setModel(m);
    return *this;
}

Node& Node::setPositionY(float y)
{
    auto m = _impl->getModel();
    m[3].y = y;
    _impl->setModel(m);
    return *this;
}

Node& Node::setPositionZ(float z)
{
    auto m = _impl->getModel();
    m[3].z = z;
    _impl->setModel(m);
    return *this;
}

Node& Node::translate(float x, float y, float z)
{
    _impl->setModel(glm::translate(_impl->getModel(), vec3{x, y, z}));
    _impl->getController().onMove(x, y, z);
    return *this;
}

Node& Node::translateX(float x)
{
    _impl->setModel(glm::translate(_impl->getModel(), vec3{x, 0.f, 0.f}));
    _impl->getController().onMove(x, 0, 0);
    return *this;
}

Node& Node::translateY(float y)
{
    _impl->setModel(glm::translate(_impl->getModel(), vec3{0.f, y, 0.f}));
    _impl->getController().onMove(0, y, 0);
    return *this;
}

Node& Node::translateZ(float z)
{
    _impl->setModel(glm::translate(_impl->getModel(), vec3{0.f, 0.f, z}));
    _impl->getController().onMove(0, 0, z);
    return *this;
}

float Node::getScaleX() const
{
    return _impl->getModel()[0].x;
}

float Node::getScaleY() const
{
    return _impl->getModel()[1].y;
}

Node& Node::setScale(float x, float y)
{
    auto m = _impl->getModel();
    m[0].x = x;
    m[1].y = y;
    _impl->setModel(m);
    return *this;
}

Node& Node::setScaleX(float x)
{
    auto m = _impl->getModel();
    m[0].x = x;
    _impl->setModel(m);
    return *this;
}

Node& Node::setScaleY(float y)
{
    auto m = _impl->getModel();
    m[1].y = y;
    _impl->setModel(m);
    return *this;
}

Node& Node::scale(float x, float y)
{
    _impl->setModel(glm::scale(_impl->getModel(), vec3{x, y, 0.f}));
    return *this;
}

Node& Node::scaleX(float x)
{
    _impl->setModel(glm::scale(_impl->getModel(), vec3{x, 0.f, 0.f}));
    return *this;
}

Node& Node::scaleY(float y)
{
    _impl->setModel(glm::scale(_impl->getModel(), vec3{0.f, y, 0.f}));
    return *this;
}

bool Node::isVisible() const
{
    return _impl->isVisible();
}

Node& Node::setVisible(bool isVisible)
{
    _impl->setVisible(isVisible);
    _impl->getController().onVisibleChanged(isVisible);
    return *this;
}

Node& Node::accept(NodeVisitor& nv)
{
    nv.visit(*this);
    return *this;
}

map<string, Node>& Node::getNodes()
{
    return _impl->getNodes();
}

Controller& Node::getController()
{
    return _impl->getController();
}

} /* namespace jupiter */

