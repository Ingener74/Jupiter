/*
 * Node.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include <iostream>

#include "Jupiter/JupiterError.h"
#include "Jupiter/NodeVisitor.h"
#include "Jupiter/Tools.h"
#include "Jupiter/Node.h"

namespace jupiter {

using namespace std;
using namespace glm;
using namespace nlohmann;

Node::Node(bool visible, std::string const& name, int tag) :
    _visible(visible), _name(name), _tag(tag) {
}

Node::Node(const Node& node) {
    *this = node;
    _nodes.clear();
    for (auto i : node._nodes) {
        auto copy = i->clone();
        copy->setParent(this);
        _nodes.emplace_back(copy);
    }
}

Node* Node::clone() {
    return new Node(*this);
}

Node* Node::setParent(Node* parent) {
    jassert(parent, "parent is nullptr");
    _parent = parent;
    return this;
}

Node* Node::getParent() {
    return _parent;
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
        nv->pop(this);
    }
    return this;
}

Node* Node::addNode(Node* node) {
    jassert(node, "node is nullptr");
    _nodes.emplace_back(node->setParent(this));
    return this;
}

Node* Node::removeNode(Node* node) {
    jassert(node, "node is nullptr");

    jassert(false, "not implemented");
//    _nodes.remove(node); // FIXME разобраться с этиим

    return this;
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

json Node::getJson() const {
    return json {
        { "Node",
            {
                { "visible", _visible },
                { "tag", _tag },
                { "name", _name },
//                { "position", {
//                        { "x", _position.x },
//                        { "y", _position.y },
//                        { "z", _position.z }}
//                },
//                { "scale",{
//                    { "x", _scale.x },
//                    { "y", _scale.y },
//                    { "z", _scale.z }}
//                },
//                { "rotation",{
//                    { "x", _rotation.x },
//                    { "y", _rotation.y },
//                    { "z", _rotation.z },
//                    { "w", _rotation.w }}
//                },
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
