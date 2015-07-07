/*
 * RenderVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include <iostream>

#include "Jupiter/Transform.h"
#include "Jupiter/Shader.h"
#include "Jupiter/Camera.h"
#include "Jupiter/Tools.h"
#include "Jupiter/Node.h"
#include "Jupiter/Sprite.h"
#include "Jupiter/RenderVisitor.h"

namespace jupiter {

using namespace std;
using namespace glm;

/*
 * Diff объекты
 * для
 * пред рендеринг
 *
 * создание списка батчей по разнице деревьев сцены
 *
 */

RenderVisitor::RenderVisitor() {
    _models.push({});
}

void RenderVisitor::begin() {
}

void RenderVisitor::push(DrawNode*){
}

void RenderVisitor::visit(DrawNode* node) {
    jassert(node, "node is invalid");



    glDrawElements(node->getMode(), node->getCount(), GL_UNSIGNED_SHORT, nullptr);
}

void RenderVisitor::pop(DrawNode*){
}

void RenderVisitor::push(Sprite*){
}

void RenderVisitor::visit(Sprite* sprite) {
    jassert(sprite, "Render visitor: sprite is nullptr");
    jassert(!_cameras.empty(), "no cameras in tree above");

    /*
     * Shader{} + Camera{Projection, View} + Object{Vertexes, Texcoords, Textures, Model}
     *
     * Shader <- Camera
     * Shader <- Object
     *
     * Shader: Uniform{type: name = value} <- Camera{}
     *
     */

    auto camera = _cameras.top();

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
    uniformProjection.set(camera->getProjectionMatrix());

    auto uniformView = shader->getUniform("View");
    uniformView.set(camera->getViewMatrix());

    auto uniformModel = shader->getUniform("Model");
    uniformModel.set(_models.top());

    static GLenum drawTypes[] = {
            GL_TRIANGLES,
            GL_TRIANGLE_FAN,
            GL_TRIANGLE_STRIP,
            GL_LINE_STRIP,
    };

    glDrawArrays(drawTypes[sprite->getShape()->getType()], 0, sprite->getShape()->getVertexCount());
}

void RenderVisitor::pop(Sprite*){
}

void RenderVisitor::push(VisualBody*){
}

void RenderVisitor::visit(VisualBody* body) {
}

void RenderVisitor::pop(VisualBody*){
}

void RenderVisitor::push(Camera* camera){
    jassert(camera, "invalid camera");
    _cameras.push(camera);
}

void RenderVisitor::visit(Camera*) {
}

void RenderVisitor::pop(Camera*){
    _cameras.pop();
}

void RenderVisitor::push(Transform* transform) {
    jassert(transform, "invalid transform");
    _models.push(_models.top() * transform->getModel());
}

void RenderVisitor::visit(Transform*) {
}

void RenderVisitor::pop(Transform*) {
    _models.pop();
}

void RenderVisitor::end() {
    for (auto & batch : _batches) {
        batch->draw();
    }
}

} /* namespace jupiter */
