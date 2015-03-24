/*
 * NodeVisitor.h
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#ifndef NODEVISITOR_H_
#define NODEVISITOR_H_

namespace jupiter {

class Node;
class Sprite;

class NodeVisitor {
public:
    NodeVisitor();
    virtual ~NodeVisitor();

    virtual void visit(Node*);
    virtual void visit(Sprite*);
};

} /* namespace jupiter */

#endif /* NODEVISITOR_H_ */
