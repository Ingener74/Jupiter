/*
 * Node.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include <iostream>

#include <Jupiter/Node.h>

namespace jupiter
{

using namespace std;

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
    return _model[0][0] < r._model[0][0];
}

bool Node::operator >(const Node& r)
{
    return _model[0][0] > r._model[0][0];
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
    return 0.f;
}

float Node::getPositionY() const
{
    return 0.f;
}

float Node::getPositionZ() const
{
    return 0.f;
}

Node& Node::setPosition(float x, float y, float z)
{
    return *this;
}

Node& Node::setPositionX(float float1)
{
    return *this;
}

Node& Node::setPositionY(float float1)
{
    return *this;
}

Node& Node::setPositionZ(float float1)
{
    return *this;
}

Node& Node::translate(float x, float y, float z)
{
    return *this;
}

Node& Node::translateX(float float1)
{
    return *this;
}

Node& Node::translateY(float float1)
{
    return *this;
}

Node& Node::translateZ(float float1)
{
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

} /* namespace jupiter */

