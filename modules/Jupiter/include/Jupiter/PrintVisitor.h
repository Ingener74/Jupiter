/*
 * PrintVisitor.h
 *
 *  Created on: Mar 25, 2015
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_PRINTVISITOR_H_
#define MODULES_JUPITER_INCLUDE_PRINTVISITOR_H_

#include "NodeVisitor.h"

namespace jupiter {

class Game;

class PrintVisitor: public NodeVisitor {
public:
    PrintVisitor(Game*);
    virtual ~PrintVisitor();

    virtual void begin();

    virtual void visit(Node*);
    virtual void visit(Sprite*);
    virtual void visit(Body*);
    virtual void visit(Camera*);

    virtual void visit(SpriteBody*);

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

private:
    int calcTabs(Node*);
    std::string tabs(int);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_PRINTVISITOR_H_ */
