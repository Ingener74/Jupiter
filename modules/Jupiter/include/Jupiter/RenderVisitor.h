/*
 * RenderVisitor.h
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#ifndef RENDERVISITOR_H_
#define RENDERVISITOR_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Jupiter/NodeVisitor.h>

namespace jupiter {

class RenderVisitor: public NodeVisitor {
public:
    RenderVisitor();
    RenderVisitor(const glm::mat4& ortho);
    virtual ~RenderVisitor();

    virtual void begin();

    virtual void visit(Node*);
    virtual void visit(Sprite*);

    virtual void end();

private:
    glm::mat4 _ortho;
};

inline RenderVisitor::RenderVisitor() {
}

inline RenderVisitor::RenderVisitor(const glm::mat4& ortho) :
    _ortho(ortho) {
}

inline RenderVisitor::~RenderVisitor() {
}

} /* namespace jupiter */

#endif /* RENDERVISITOR_H_ */
