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
    #include <stack>

    #include "Ref.h"
#endif

#include "Jupiter/NodeVisitor.h"

namespace jupiter {

class Camera;
class VisualBody;

class RenderVisitor: public NodeVisitor {
public:
    RenderVisitor() = default;
    RenderVisitor(Camera*);

    virtual ~RenderVisitor() = default;

    virtual void begin();

    virtual void visit(Sprite*);
    virtual void visit(VisualBody*);
    virtual void visit(Camera*);

    virtual void end();

private:
    Ref<Camera> _camera; // TODO должна быть не здесь а в дереве узлов
};

} /* namespace jupiter */

#endif /* RENDERVISITOR_H_ */
