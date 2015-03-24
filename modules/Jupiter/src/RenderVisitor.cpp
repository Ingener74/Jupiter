/*
 * RenderVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include "Jupiter/Tools.h"
#include "Jupiter/Node.h"
#include "Jupiter/Sprite.h"
#include "Jupiter/RenderVisitor.h"

namespace jupiter {

void jupiter::RenderVisitor::visit(Node* node) {
}

void jupiter::RenderVisitor::visit(Sprite* sprite) {
    if (!sprite)
        throw JupiterError("Render visitor: sprite is nullptr");

    auto shader = sprite->getProgram();

    shader->use();

    auto uniformTexture   = shader->getUniform("uTEX");
    auto uniformMVP       = shader->getUniform("uMVP");
    auto position         = shader->getAttribute("aPOS");
    auto textureCoords    = shader->getAttribute("aTEX");

    glActiveTexture(GL_TEXTURE0);
    sprite->getTexture()->bind();
    glEnable(GL_TEXTURE_2D);
    uniformTexture.set(sprite->getTexture());

    position.set(sprite->getShape());
    textureCoords.set(sprite->getShape());

    glm::mat4 mvp = _ortho; // * sprite->getModelMatrix();
    uniformMVP.set(mvp);

    static GLenum drawTypes[] = {
            GL_TRIANGLES,
            GL_TRIANGLE_FAN,
            GL_TRIANGLE_STRIP,
            GL_LINE_STRIP,
    };

    glDrawArrays(drawTypes[sprite->getShape()->getType()], 0, sprite->getShape()->getVertexCount());
    CHECK_GL_ERROR
}

void RenderVisitor::draw() {
}

} /* namespace jupiter */
