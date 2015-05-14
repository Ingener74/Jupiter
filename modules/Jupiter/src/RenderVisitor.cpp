/*
 * RenderVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include <iostream>

#include "Jupiter/Shader.h"
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
    jassert(sprite, "Render visitor: sprite is nullptr")

    auto shader = sprite->getProgram();

    shader->use();

    auto uniformTexture = shader->getUniform("Texture");
    glActiveTexture(GL_TEXTURE0);
    sprite->getTexture()->bind();
    uniformTexture.set(0);          // texture unit not texture id

    auto position = shader->getAttribute("VertexPosition");
    position.set(sprite->getShape());

    auto textureCoords = shader->getAttribute("VertexTexCoord");
    textureCoords.set(sprite->getShape());

    auto uniformProjection = shader->getUniform("Projection");
    uniformProjection.set(_camera->getProjectionMatrix());

    auto uniformView = shader->getUniform("View");
    uniformView.set(_camera->getViewMatrix());

    auto uniformModel = shader->getUniform("Model");
    uniformModel.set(sprite->getModel());

    static GLenum drawTypes[] = {
            GL_TRIANGLES,
            GL_TRIANGLE_FAN,
            GL_TRIANGLE_STRIP,
            GL_LINE_STRIP,
    };

    glDrawArrays(drawTypes[sprite->getShape()->getType()], 0, sprite->getShape()->getVertexCount());
}

void RenderVisitor::end() {
}

} /* namespace jupiter */
