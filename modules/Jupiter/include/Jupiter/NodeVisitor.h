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
class Body;
class Camera;
class SpriteBody;
class VisualBody;
class Joint;

class RevoluteJoint;
class DistanceJoint;
class RopeJoint;
class MotorJoint;
class GearJoint;
class WheelJoint;
class FrictionJoint;
class MouseJoint;
class PrismaticJoint;
class PulleyJoint;
class WeldJoint;

class NodeVisitor: virtual public RCO {
public:
    NodeVisitor();
    virtual ~NodeVisitor();

    virtual void begin();

    virtual void push(Node*);
    virtual void pop();

    virtual void visit(Node*);
    virtual void visit(Sprite*);
    virtual void visit(Body*);
    virtual void visit(SpriteBody*);
    virtual void visit(VisualBody*);

    virtual void visit(Camera*);

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
    std::stack<Node*> _stack;
};

} /* namespace jupiter */

#endif /* NODEVISITOR_H_ */
