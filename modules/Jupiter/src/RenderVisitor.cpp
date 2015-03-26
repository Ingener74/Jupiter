/*
 * RenderVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include <iostream>
#include "Jupiter/Tools.h"
#include "Jupiter/Node.h"
#include "Jupiter/Sprite.h"
#include "Jupiter/RenderVisitor.h"

namespace jupiter {

using namespace std;
using namespace glm;

void jupiter::RenderVisitor::visit(Node* node) {
}

RenderVisitor::RenderVisitor(const glm::mat4& projection, const glm::mat4& view) :
    projection(projection), view(view) {
}

void RenderVisitor::begin() {
}

void jupiter::RenderVisitor::visit(Sprite* sprite) {
    if (!sprite)
        throw JupiterError("Render visitor: sprite is nullptr");

    auto shader = sprite->getProgram();

    shader->use();

    auto uniformTexture = shader->getUniform("uTEX");
    glActiveTexture(GL_TEXTURE0);
    sprite->getTexture()->bind();
    uniformTexture.set(0);          // texture unit not texture id

    auto position = shader->getAttribute("aPOS");
    position.set(sprite->getShape());

    auto textureCoords = shader->getAttribute("aTEX");
    textureCoords.set(sprite->getShape());

    auto uniformMVP = shader->getUniform("uMVP");
    mat4 mvp = projection * view * sprite->getModel();
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

void RenderVisitor::end() {
}

} /* namespace jupiter */
