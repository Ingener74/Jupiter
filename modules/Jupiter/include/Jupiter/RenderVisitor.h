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

class RenderData{
public:
    RenderData(){}
    virtual ~RenderData(){}
};

class RenderBatch: public RCO {
public:
    RenderBatch() = default;
    virtual ~RenderBatch() = default;

    void setRenderData(RenderData*){} // Attributes

    void setCamera(Camera*){} // model matrix
    void setShader(Shader*){} // projection and view matrix

    void draw(){}
};

class RenderVisitor: public NodeVisitor {
public:
    RenderVisitor();

    virtual ~RenderVisitor() = default;

    virtual void begin();

    VISIT_(DrawNode)
    VISIT_(Sprite)
    VISIT_(VisualBody)
    VISIT_(Camera)
    VISIT_(Transform)

    virtual void end();

private:
    std::stack<glm::mat4> _models;
    std::stack<Camera*> _cameras;

    Shader* _shader = nullptr;

    std::list<Ref<RenderBatch>> _batches;
};

} /* namespace jupiter */

#endif /* RENDERVISITOR_H_ */
