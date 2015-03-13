/*
 * Node.h
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_

#include <set>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Jupiter/Controller.h"
#include "Jupiter/JupiterError.h"

namespace jupiter {

class NodeVisitor;

class Node {
public:
    Node(const std::string& name);
    virtual ~Node();

    void addNode(Node* node);

    float getRotationX() const;
    float getRotationY() const;
    float getRotationZ() const;

    Node* setRotation(float x, float y, float z);
    Node* setRotationX(float x);
    Node* setRotationY(float y);
    Node* setRotationZ(float z);

    Node* rotate(float x, float y, float z);
    Node* rotateX(float x);
    Node* rotateY(float y);
    Node* rotateZ(float z);

    float getPositionX() const;
    float getPositionY() const;
    float getPositionZ() const;

    Node* setPosition(float x, float y, float z);
    Node* setPositionX(float x);
    Node* setPositionY(float y);
    Node* setPositionZ(float z);

    Node* translate(float x, float y, float z);
    Node* translateX(float x);
    Node* translateY(float y);
    Node* translateZ(float z);

    float getScaleX() const;
    float getScaleY() const;

    Node* setScale(float x, float y);
    Node* setScaleX(float x);
    Node* setScaleY(float y);

    Node* scale(float x, float y);
    Node* scaleX(float x);
    Node* scaleY(float y);

    bool isVisible() const;
    Node* setVisible(bool isVisible);

    Node* accept(NodeVisitor* nv);

    Node* setController(Controller* controller);
    Controller* getController();

protected:
    template<typename T, typename ... Args>
    void createNode(Args ... args);

    struct NodePtr {
        using Created = bool;

        Node* node = nullptr;
        Created created = false;

        NodePtr(Node*, Created created = false);

        bool operator <(const NodePtr& r) const;
        bool operator >(const NodePtr& r) const;
        bool operator ==(const NodePtr& r) const;
        bool operator !=(const NodePtr& r) const;
    };

    bool visible = true;
    glm::mat4 model;
    Controller* controller = nullptr;
    std::set<NodePtr> nodes;

public:
    static int leakCheck;
};

inline Node::Node(const std::string& name) {
    ++leakCheck;
}

inline void Node::addNode(Node* node) {
    if (!node)
        throw JupiterError("Node add nullptr node");

    nodes.insert(NodePtr { node });
}

inline float Node::getRotationX() const {
    return 0.f;
}

inline float Node::getRotationY() const {
    return 0.f;
}

inline float Node::getRotationZ() const {
    return 0.f;
}

inline Node* Node::setRotation(float x, float y, float z) {
    if (controller)
        controller->onRotate(x, y, z);

    return this;
}

inline Node* Node::setRotationX(float x) {
    if (controller)
        controller->onRotate(x, 0, 0);

    return this;
}

inline Node* Node::setRotationY(float y) {
    if (controller)
        controller->onRotate(0, y, 0);

    return this;
}

inline Node* Node::setRotationZ(float z) {
    if (controller)
        controller->onRotate(0, 0, z);

    return this;
}

inline Node* Node::rotate(float x, float y, float z) {
    if (controller)
        controller->onRotate(x, y, z);

    return this;
}

inline Node* Node::rotateX(float x) {
    if (controller)
        controller->onRotate(x, 0, 0);

    return this;
}

inline Node* Node::rotateY(float y) {
    if (controller)
        controller->onRotate(0, y, 0);

    return this;
}

inline Node* Node::rotateZ(float z) {
    if (controller)
        controller->onRotate(0, 0, z);

    return this;
}

inline float Node::getPositionX() const {
    return model [ 3 ].x;
}

inline float Node::getPositionY() const {
    return model [ 3 ].y;
}

inline float Node::getPositionZ() const {
    return model [ 3 ].z;
}

inline Node* Node::setPosition(float x, float y, float z) {
    model [ 3 ].x = x;
    model [ 3 ].y = y;
    model [ 3 ].z = z;
    if (controller)
        controller->onPositionChanged(x, y, z);

    return this;
}

inline Node* Node::setPositionX(float x) {
    model [ 3 ].x = x;
    if (controller)
        controller->onPositionChanged(x, 0.f, 0.f);

    return this;
}

inline Node* Node::setPositionY(float y) {
    model [ 3 ].y = y;
    if (controller)
        controller->onPositionChanged(0.f, y, 0.f);

    return this;
}

inline Node* Node::setPositionZ(float z) {
    model [ 3 ].z = z;
    if (controller)
        controller->onPositionChanged(0.f, 0.f, z);

    return this;
}

inline Node* Node::translate(float x, float y, float z) {
    model = glm::translate(model, glm::vec3 { x, y, z });
    if (controller)
        controller->onMove(x, y, z);

    return this;
}

inline Node* Node::translateX(float x) {
    model = glm::translate(model, glm::vec3 { x, 0.f, 0.f });
    if (controller)
        controller->onMove(x, 0, 0);

    return this;
}

inline Node* Node::translateY(float y) {
    model = glm::translate(model, glm::vec3 { 0.f, y, 0.f });
    if (controller)
        controller->onMove(0, y, 0);

    return this;
}

inline Node* Node::translateZ(float z) {
    model = glm::translate(model, glm::vec3 { 0.f, 0.f, z });
    if (controller)
        controller->onMove(0, 0, z);

    return this;
}

inline float Node::getScaleX() const {
    return model [ 0 ].x;
}

inline float Node::getScaleY() const {
    return model [ 1 ].y;
}

inline Node* Node::setScale(float x, float y) {
    model [ 0 ].x = x;
    model [ 1 ].y = y;
    return this;
}

inline Node* Node::setScaleX(float x) {
    model [ 0 ].x = x;
    return this;
}

inline Node* Node::setScaleY(float y) {
    model [ 1 ].y = y;
    return this;
}

inline Node* Node::scale(float x, float y) {
    model = glm::scale(model, glm::vec3 { x, y, 0.f });
    return this;
}

inline Node* Node::scaleX(float x) {
    model = glm::scale(model, glm::vec3 { x, 0.f, 0.f });
    return this;
}

inline Node* Node::scaleY(float y) {
    model = glm::scale(model, glm::vec3 { 0.f, y, 0.f });
    return this;
}

inline bool Node::isVisible() const {
    return visible;
}

inline Node* Node::setVisible(bool isVisible) {
    visible = isVisible;
    if (controller)
        controller->onVisibleChanged(isVisible);

    return this;
}

inline Node* Node::setController(Controller* controller) {
    Node::controller = controller;
    return this;
}

inline Controller* Node::getController() {
    return controller;
}

template<typename T, typename ... Args>
inline void Node::createNode(Args ... args) {
    nodes.insert(NodePtr { new T(args...), true });
}

inline Node::NodePtr::NodePtr(Node* node, Created created) :
    node(node), created(created) {
}

inline bool Node::NodePtr::operator <(const NodePtr& r) const {
    return node->model [ 3 ].z < r.node->model [ 3 ].z || node < r.node;
}

inline bool Node::NodePtr::operator >(const NodePtr& r) const {
    return node->model [ 3 ].z > r.node->model [ 3 ].z || node > r.node;
}

inline bool Node::NodePtr::operator ==(const NodePtr& r) const {
    return node == r.node;
}

inline bool Node::NodePtr::operator !=(const NodePtr& r) const {
    return node != r.node;
}

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_ */
