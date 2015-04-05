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
    RenderVisitor() = default;
    RenderVisitor(const glm::mat4& projection, const glm::mat4& view);
    virtual ~RenderVisitor() = default;

    void setView(const glm::mat4& view);

    virtual void begin();

    virtual void visit(Sprite*);

    virtual void end();

private:
    glm::mat4 projection, view;
};

} /* namespace jupiter */

#endif /* RENDERVISITOR_H_ */
