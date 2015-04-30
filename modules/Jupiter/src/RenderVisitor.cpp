/*
 * RenderVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include <iostream>

#include "Jupiter/Camera.h"
#include "Jupiter/Tools.h"
#include "Jupiter/Node.h"
#include "Jupiter/Sprite.h"
#include "Jupiter/RenderVisitor.h"

namespace jupiter {

using namespace std;
using namespace glm;

RenderVisitor::RenderVisitor(Camera* camera) {
    _camera = camera;
}

void RenderVisitor::begin() {
}

void RenderVisitor::visit(Sprite* sprite) {
    if (!sprite)
        throw JupiterError("Render visitor: sprite is nullptr");

    auto shader = sprite->getProgram();

    CHECK_GL_ERROR

    shader->use();
    CHECK_GL_ERROR

    auto uniformTexture = shader->getUniform("Texture");
    glActiveTexture(GL_TEXTURE0);
    sprite->getTexture()->bind();
    uniformTexture.set(0);          // texture unit not texture id
    CHECK_GL_ERROR

    auto position = shader->getAttribute("VertexPosition");
    position.set(sprite->getShape());
    CHECK_GL_ERROR

    auto textureCoords = shader->getAttribute("VertexTexCoord");
    textureCoords.set(sprite->getShape());
    CHECK_GL_ERROR

    auto uniformProjection = shader->getUniform("Projection");
    uniformProjection.set(_camera->getProjectionMatrix());
    CHECK_GL_ERROR

    auto uniformView = shader->getUniform("View");
    uniformView.set(_camera->getViewMatrix());
    CHECK_GL_ERROR

    auto uniformModel = shader->getUniform("Model");
    uniformModel.set(sprite->getModel());
    CHECK_GL_ERROR

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
