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

#include <Jupiter/Node.h>

namespace jupiter
{

using namespace std;
using namespace glm;

Node::Node(const Controller&, std::map<std::string, Node> nodes)
{
}

Node::Node(const std::string& nodeName)
{
}

Node::~Node()
{
}

bool Node::operator <(const Node& r)
{
    return _model[3].z < r._model[3].z;
}

bool Node::operator >(const Node& r)
{
    return _model[3].z > r._model[3].z;
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
    return *this;
}

Node& Node::setRotationX(float float1)
{
    return *this;
}

Node& Node::setRotationY(float float1)
{
    return *this;
}

Node& Node::setRotationZ(float float1)
{
    return *this;
}

Node& Node::rotate(float x, float y, float z)
{
    return *this;
}

Node& Node::rotateX(float float1)
{
    return *this;
}

Node& Node::rotateY(float float1)
{
    return *this;
}

Node& Node::rotateZ(float float1)
{
    return *this;
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

Node& Node::setPosition(float x, float y, float z)
{
    _model[3].x = x;
    _model[3].y = y;
    _model[3].z = z;
    return *this;
}

Node& Node::setPositionX(float x)
{
    _model[3].x = x;
    return *this;
}

Node& Node::setPositionY(float y)
{
    _model[3].y = y;
    return *this;
}

Node& Node::setPositionZ(float z)
{
    _model[3].z = z;
    return *this;
}

Node& Node::translate(float x, float y, float z)
{
    _model = glm::translate(_model, vec3{x, y, z});
    return *this;
}

Node& Node::translateX(float x)
{
    _model = glm::translate(_model, vec3{x, 0.f, 0.f});
    return *this;
}

Node& Node::translateY(float y)
{
    _model = glm::translate(_model, vec3{0.f, y, 0.f});
    return *this;
}

Node& Node::translateZ(float z)
{
    _model = glm::translate(_model, vec3{0.f, 0.f, z});
    return *this;
}

float Node::getScaleX() const
{
    return 1.f;
}

float Node::getScaleY() const
{
    return 1.f;
}

Node& Node::setScale(float x, float y)
{
    return *this;
}

Node& Node::setScaleX(float float1)
{
    return *this;
}

Node& Node::setScaleY(float float1)
{
    return *this;
}

Node& Node::scale(float x, float y)
{
    return *this;
}

Node& Node::scaleX(float float1)
{
    return *this;
}

Node& Node::scaleY(float float1)
{
    return *this;
}

bool Node::isVisible() const
{
    return true;
}

Node& Node::setVisible(bool bool1)
{
    return *this;
}

Node& Node::accept(const NodeVisitor&)
{
    return *this;
}

} /* namespace jupiter */

