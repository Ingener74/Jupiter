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

class RenderVisitor: public NodeVisitor {
public:
    RenderVisitor();

    virtual ~RenderVisitor() = default;

    virtual void begin();

    VISIT_(Sprite)
    VISIT_(VisualBody)
    VISIT_(Camera)
    VISIT_(Transform)

    virtual void end();

private:
    std::stack<glm::mat4> _models;
    std::stack<Camera*> _cameras;

    Shader* _shader = nullptr;
};

} /* namespace jupiter */

#endif /* RENDERVISITOR_H_ */
