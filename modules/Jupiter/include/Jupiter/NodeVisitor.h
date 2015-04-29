/*
 * NodeVisitor.h
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#ifndef NODEVISITOR_H_
#define NODEVISITOR_H_

#ifdef SWIG
#else

    #include <stack>

#endif

namespace jupiter {

class Node;
class Sprite;

class NodeVisitor {
public:
    NodeVisitor();
    virtual ~NodeVisitor();

    virtual void begin();

    virtual void push(Node*);
    virtual void pop();

    virtual void visit(Node*);
    virtual void visit(Sprite*);

    virtual void end();

protected:
    std::stack<Node*> stack;
};

} /* namespace jupiter */

#endif /* NODEVISITOR_H_ */
