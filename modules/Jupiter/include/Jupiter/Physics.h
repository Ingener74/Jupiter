/*
 * Box2DVisitor.h
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_PHYSICS_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_PHYSICS_H_

#ifdef SWIG
#else
    #include <memory>
#endif

#include "NodeVisitor.h"

class b2World;
class b2ContactListener;

namespace jupiter {

class Physics: public NodeVisitor {
public:
    Physics(float timeStep, int positionIterations = 2, int velocityIterations = 6);
    virtual ~Physics();

    virtual void begin();

    virtual void push(Node*);
    virtual void pop();

    virtual void visit(Body*);

    virtual void end();

    b2World* getWorld();

    float getTimeStep() const;
    Physics* setTimeStep(float timeStep);

    int getPositionIterations() const;
    Physics* setPositionIterations(int positionIterations);

    int getVelocityIterations() const;
    Physics* setVelocityIterations(int velocityIterations);

    void collide(Body* a, Body* b);

private:
    std::unique_ptr<b2World> _world;
    float _timeStep = 0.f;
    int _positionIterations = 2;
    int _velocityIterations = 6;
    std::unique_ptr<b2ContactListener> _contactListener;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_PHYSICS_H_ */
