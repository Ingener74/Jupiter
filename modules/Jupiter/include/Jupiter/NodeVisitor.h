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

#include "RCO.h"

namespace jupiter {

class Node;
class Sprite;
class Box2dNode;
class Camera;
class SpriteBox2d;
class Joint;

class NodeVisitor: virtual public RCO {
public:
    NodeVisitor();
    virtual ~NodeVisitor();

    virtual void begin();

    virtual void push(Node*);
    virtual void pop();

    virtual void visit(Node*);
    virtual void visit(Sprite*);
    virtual void visit(Box2dNode*);
    virtual void visit(Camera*);

    virtual void visit(SpriteBox2d*);

    virtual void visit(Joint*);
    virtual void visit(RevoluteJoint*);
    virtual void visit(DistanceJoint*);
    virtual void visit(RopeJoint*);
    virtual void visit(MotorJoint*);
    virtual void visit(GearJoint*);
    virtual void visit(WheelJoint*);
    virtual void visit(FrictionJoint*);
    virtual void visit(MouseJoint*);
    virtual void visit(PrismaticJoint*);
    virtual void visit(PulleyJoint*);
    virtual void visit(WeldJoint*);

    virtual void end();

protected:
    std::stack<Node*> stack;
};

} /* namespace jupiter */

#endif /* NODEVISITOR_H_ */
