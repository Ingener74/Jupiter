/*
 * RenderVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include <Jupiter/RenderVisitor.h>
#include <Jupiter/Node.h>
#include <Jupiter/Sprite.h>

namespace jupiter {

void jupiter::RenderVisitor::visit(Node* node) {
}

void jupiter::RenderVisitor::visit(Sprite* sprite) {
    if (!sprite)
        throw JupiterError("Render visitor: sprite is nullptr");

    /*
     * draw sprite
     */

    auto shader = sprite->getProgram();
    shader->use();

    sprite->getTexture()->bind();

    /*
     * draw shape with program
     */

    auto texture       = shader->getUniformLocation("uTEX");
    auto uniformMVP    = shader->getUniformLocation("uMVP");
    auto position      = shader->getAttributeLocation("aPOS");
    auto textureCoords = shader->getAttributeLocation("aTEX");

    glUniform1i(texture, 0);
    glEnableVertexAttribArray(position);
    glEnableVertexAttribArray(textureCoords);

    auto shape = sprite->getShape();

    const GLfloat * spriteVertex = nullptr; // s->getVertex();
    uint32_t spriteVertexCount = 0; // s->getVertexCount();

    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &spriteVertex[0]);
    glVertexAttribPointer(textureCoords, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &spriteVertex[3]);

    glm::mat4 mvp = _ortho; // * sprite->getModelMatrix();

    glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, glm::value_ptr(mvp));

    static GLenum drawTypes[] = {
            GL_TRIANGLES,
            GL_TRIANGLE_FAN,
            GL_TRIANGLE_STRIP,
            GL_LINE_STRIP,
    };

    glDrawArrays(drawTypes[shape->getType()], 0, spriteVertexCount);

    glDisableVertexAttribArray(position);
    glDisableVertexAttribArray(textureCoords);
}

void RenderVisitor::draw() {
}

} /* namespace jupiter */
