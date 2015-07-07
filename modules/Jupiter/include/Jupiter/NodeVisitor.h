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

#define VISIT(X)                   \
    virtual void push(class X*){}  \
    virtual void visit(class X*){} \
    virtual void pop(class X*){}   \

#define VISIT_(X)           \
    virtual void push(X*);  \
    virtual void visit(X*); \
    virtual void pop(X*);   \

class Game;

class NodeVisitor: virtual public RCO {
public:
    NodeVisitor() = default;
    virtual ~NodeVisitor() = default;

    virtual void begin(){}

    VISIT(Node)

    VISIT(DrawNode)
    VISIT(Transform)
    VISIT(Sprite)
    VISIT(Body)
    VISIT(SpriteBody)
    VISIT(VisualBody)

    VISIT(Camera)

    VISIT(Joint)
    VISIT(RevoluteJoint)
    VISIT(DistanceJoint)
    VISIT(RopeJoint)
    VISIT(MotorJoint)
    VISIT(GearJoint)
    VISIT(WheelJoint)
    VISIT(FrictionJoint)
    VISIT(MouseJoint)
    VISIT(PrismaticJoint)
    VISIT(PulleyJoint)
    VISIT(WeldJoint)

    virtual void end(){}

    Game* getGame();
    NodeVisitor* setGame(Game* game);

protected:
    Game* _game = nullptr;
};

} /* namespace jupiter */

#endif /* NODEVISITOR_H_ */
