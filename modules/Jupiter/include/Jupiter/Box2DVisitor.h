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
    #include <cstdint>
    #include <memory>
#endif

#include "NodeVisitor.h"

class b2World;

namespace jupiter {

class Box2DVisitor: public NodeVisitor {
public:
    Box2DVisitor(float timeStep, int32_t positionIterations = 2, int32_t velocityIterations = 6);
    virtual ~Box2DVisitor();

    virtual void begin();

    virtual void push(Node*);
    virtual void pop();

    virtual void visit(Box2dNode*);

    virtual void end();

    b2World* getWorld();

    float getTimeStep() const;
    Box2DVisitor* setTimeStep(float timeStep = 0.f);

    int32_t getPositionIterations() const;
    Box2DVisitor* setPositionIterations(int32_t positionIterations = 2);

    int32_t getVelocityIterations() const;
    Box2DVisitor* setVelocityIterations(int32_t velocityIterations = 6);

private:
    std::unique_ptr<b2World> _world;
    float _timeStep = 0.f;
    int32_t _positionIterations = 2;
    int32_t _velocityIterations = 6;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_BOX2DVISITOR_H_ */
