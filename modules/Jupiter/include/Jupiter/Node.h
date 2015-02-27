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

#include <glm/glm.hpp>

#include "Jupiter/Controller.h"
#include "Jupiter/Aware.h"

namespace jupiter
{

class NodeVisitor;

class Node: public Object{
public:
    struct NodePtr
    {
        Node* node = nullptr;

        NodePtr(Node* node) :
                node(node)
        {
        }

        bool operator<(const NodePtr&) const;
        bool operator>(const NodePtr&) const;
        bool operator==(const NodePtr&) const;
        bool operator!=(const NodePtr&) const;
    };

    Node(const std::string& name);
    virtual ~Node();

    void addNode(Node*);
    std::set<NodePtr>::iterator begin();
    std::set<NodePtr>::iterator end();

    float getRotationX() const;
    float getRotationY() const;
    float getRotationZ() const;

    Node* setRotation(float x, float y, float z);
    Node* setRotationX(float);
    Node* setRotationY(float);
    Node* setRotationZ(float);

    Node* rotate(float x, float y, float z);
    Node* rotateX(float);
    Node* rotateY(float);
    Node* rotateZ(float);

    float getPositionX() const;
    float getPositionY() const;
    float getPositionZ() const;

    Node* setPosition(float x, float y, float z);
    Node* setPositionX(float);
    Node* setPositionY(float);
    Node* setPositionZ(float);

    Node* translate(float x, float y, float z);
    Node* translateX(float);
    Node* translateY(float);
    Node* translateZ(float);

    float getScaleX() const;
    float getScaleY() const;

    Node* setScale(float x, float y);
    Node* setScaleX(float);
    Node* setScaleY(float);

    Node* scale(float x, float y);
    Node* scaleX(float);
    Node* scaleY(float);

    bool isVisible() const;
    Node* setVisible(bool);

    Node* accept(NodeVisitor*);

    Controller* getController();

protected:
    bool visible = true;
    glm::mat4 model;
    Controller* controller = nullptr;
    std::set<NodePtr> nodes;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_ */
