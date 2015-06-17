/*
 * Node.h
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_

#ifdef SWIG
    #pragma SWIG nowarn=362
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
    Node();
    virtual ~Node();

    Node(const Node&);
    virtual Node* clone();

    Node* addNode(Node*);
    Node* removeNode(Node*);

    virtual Node* setParent(Node*);
    virtual Node* getParent();

    bool isVisible() const;
    Node* setVisible(bool isVisible);

    int getTag() const;
    Node* setTag(int tag);

    std::string getName() const;
    Node* setName(std::string name);

    virtual Node* accept(NodeVisitor*);

    virtual nlohmann::json getJson() const;
    friend std::ostream& operator<<(std::ostream&, Node const&);

protected:
    bool                    _visible   = true;

    int                     _tag       = -1;
    std::string             _name;

    std::list<Ref<Node>>    _nodes;
    Node*                   _parent    = nullptr;

    Node& operator=(const Node&) = default;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_ */
