/*
 * RenderVisitor.h
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#ifndef RENDERVISITOR_H_
#define RENDERVISITOR_H_

#ifdef SWIG
#else
#endif

#include "Jupiter/NodeVisitor.h"

namespace jupiter {

class Camera;

class RenderVisitor: public NodeVisitor {
public:
    RenderVisitor() = default;
    RenderVisitor(Camera*);

    virtual ~RenderVisitor() = default;

    virtual void begin();

    virtual void visit(Sprite*);

    virtual void end();

private:
    Camera* _camera = nullptr;
};

} /* namespace jupiter */

#endif /* RENDERVISITOR_H_ */
