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
using namespace nlohmann;

Node::Node() {
}

Node::~Node() {
}

Node::Node(const Node& node){
    clone(const_cast<Node*>(&node));
}

Node* Node::clone(Node* node) {
    jassert(node, "node is invalid");
    *this = *node;
    return this;
}

Node* Node::addNode(Node* node) {
    jassert(node, "node is nullptr");
    _nodes.emplace_back(node->setParent(this));
    return this;
}

Node* Node::removeNode(Node* node) {
    jassert(node, "node is nullptr");
//    _nodes.remove(node); // FIXME разобраться с этиим
    return this;
}

Node* Node::setParent(Node* parent) {
    jassert(parent, "parent is nullptr");
    _parent = parent;
    return this;
}

Node* Node::getParent() {
    return _parent;
}

float Node::getRotationX() const {
    return glm::axis(_rotation).x;
}

float Node::getRotationY() const {
    return glm::axis(_rotation).y;
}

float Node::getRotationZ() const {
    return glm::axis(_rotation).z;
}

float Node::getRotationAngle() const {
    return glm::angle(_rotation);
}

Node* Node::setRotation(float x, float y, float z, float angle) {
    _rotation = glm::rotate(quat{}, angle, vec3(x, y, z));
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
    _rotation = glm::rotate(_rotation, angle, vec3(x, y, z));
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
    if (_moveListener)
        _moveListener->move(_position.x, _position.y, _position.z);
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
    if (_moveListener)
        _moveListener->move(_position.x, _position.y, _position.z);
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
    if (_scaleListener)
        _scaleListener->scale(_scale.x, _scale.y, _scale.z);
    return this;
}

Node* Node::setScaleF(float scale) {
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
    if (_scaleListener)
        _scaleListener->scale(_scale.x, _scale.y, _scale.z);
    return this;
}

Node* Node::scaleF(float s) {
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

int Node::getTag() const {
    return _tag;
}

Node* Node::setTag(int tag) {
    _tag = tag;
    return this;
}

std::string Node::getName() const {
    return _name;
}

Node* Node::setName(std::string name) {
    _name = name;
    return this;
}

Node* Node::accept(NodeVisitor* nv) {
    jassert(nv, "visitor is nullptr");
    if (_visible) {
        nv->push(this);
        nv->visit(this);
        for (auto i : _nodes) {
            jassert(i, "invalid node");
            i->accept(nv);
        }
        nv->pop();
    }
    return this;
}

Node* Node::setMoveListener(MoveListener* moveListener) {
    jassert(moveListener, "move listener is nullptr");
    _moveListener = moveListener;
    _moveListener->setNode(this);
    return this;
}

MoveListener* Node::getMoveListener() {
    jassert(_moveListener, "no move listener");
    return _moveListener.get();
}

Node* Node::setScaleListener(ScaleListener* listener) {
    jassert(listener, "scale listener is nullptr");
    _scaleListener = listener;
    _scaleListener->setNode(this);
    return this;
}

ScaleListener* Node::getScaleListener() {
    jassert(_scaleListener, "no scale listener");
    return _scaleListener.get();
}

Node* Node::setRotationListener(RotationListener* listener) {
    jassert(listener, "rotation listener is nullptr");
    _rotationListener = listener;
    _rotationListener->setNode(this);
    return this;
}

RotationListener* Node::getRotationListener() {
    jassert(_rotationListener, "rotation listener is nullptr");
    return _rotationListener.get();
}

glm::mat4 Node::getModel() const {
    return glm::translate( { }, _position) * glm::mat4_cast(_rotation) * glm::scale( { }, _scale);
}

json Node::getJson() const {
    return json {
        { "Node",
            {
                { "visible", _visible },
                { "tag", _tag },
                { "name", _name },
                { "position",{
                        { "x", _position.x },
                        { "y", _position.y },
                        { "z", _position.z }}
                },
                { "scale",{
                    { "x", _scale.x },
                    { "y", _scale.y },
                    { "z", _scale.z }}
                },
                { "rotation",{
                    { "x", _rotation.x },
                    { "y", _rotation.y },
                    { "z", _rotation.z },
                    { "w", _rotation.w }}
                },
                {"nodes", [=]{
                    nlohmann::json nodes;
                    for(auto node: _nodes)
                        nodes.push_back(node->getJson());
                    return nodes;
                }()},
            }
        }};
}

ostream& operator<<(ostream& out, Node const& r) {
    return out << setw(4) << r.getJson();
}

} /* namespace jupiter */
