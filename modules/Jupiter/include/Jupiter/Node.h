/*
 * Node.h
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_

#ifdef SWIG
#else
    #include <list>
    #include <string>
    #include <json.hpp>

    #include "Ref.h"
#endif

namespace jupiter {

class NodeVisitor;

class Node: public RCO {
public:
    Node(bool visible = true, std::string const& name = "Node", int tag = -1);
    Node(const Node&);

    virtual ~Node() = default;

    virtual Node* clone();

    virtual Node* setParent(Node*);
    virtual Node* getParent();

    virtual Node* accept(NodeVisitor*);

    Node* addNode(Node*);
    Node* removeNode(Node*);

    int index(Node*);

    bool isVisible() const;
    Node* setVisible(bool isVisible);

    int getTag() const;
    Node* setTag(int tag);

    std::string getName() const;
    Node* setName(std::string name);

    virtual nlohmann::json getJson() const;
    friend std::ostream& operator<<(std::ostream&, Node const&);

protected:
    bool                    _visible   = true;

    std::string             _name;
    int                     _tag       = -1;

    std::list<Ref<Node>>    _nodes;
    Node*                   _parent    = nullptr;

    Node& operator=(const Node&) = default;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_ */
