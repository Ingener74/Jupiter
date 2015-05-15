/*
 * Box2DVisitor.h
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_BOX2DVISITOR_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_BOX2DVISITOR_H_

#ifdef SWIG
#else
    #include <memory>
#endif

#include "NodeVisitor.h"

class b2World;
class b2ContactListener;

namespace jupiter {

class Box2dVisitor: public NodeVisitor {
public:
    Box2dVisitor(float timeStep, int positionIterations = 2, int velocityIterations = 6);
    virtual ~Box2dVisitor();

    virtual void begin();

    virtual void push(Node*);
    virtual void pop();

    virtual void visit(Box2dNode*);

    virtual void end();

    b2World* getWorld();

    float getTimeStep() const;
    Box2dVisitor* setTimeStep(float timeStep = 0.f);

    int getPositionIterations() const;
    Box2dVisitor* setPositionIterations(int positionIterations = 2);

    int getVelocityIterations() const;
    Box2dVisitor* setVelocityIterations(int velocityIterations = 6);

private:
    std::unique_ptr<b2World> _world;
    float _timeStep = 0.f;
    int _positionIterations = 2;
    int _velocityIterations = 6;
    std::unique_ptr<b2ContactListener> _contactListener;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_BOX2DVISITOR_H_ */
