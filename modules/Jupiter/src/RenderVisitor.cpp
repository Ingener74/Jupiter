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

//    glUniform1i(texture, 0);
//    glEnableVertexAttribArray(position);
//    glEnableVertexAttribArray(textureCoords);

    auto texture       = shader->getUniform("uTEX");
    auto uniformMVP    = shader->getUniform("uMVP");
    auto position      = shader->getAttribute("aPOS");
    auto textureCoords = shader->getAttribute("aTEX");

    auto shape = sprite->getShape();

    const GLfloat * spriteVertex = nullptr; // s->getVertex();
    uint32_t spriteVertexCount = 0; // s->getVertexCount();

//    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &spriteVertex[0]);
//    glVertexAttribPointer(textureCoords, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &spriteVertex[3]);

    position.setData(shape);
    textureCoords.setData(shape);

    glm::mat4 mvp = _ortho; // * sprite->getModelMatrix();
    glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, glm::value_ptr(mvp));

    // uniformMVP.setData(glm::value_ptr(mvp));

    static GLenum drawTypes[] = {
            GL_TRIANGLES,
            GL_TRIANGLE_FAN,
            GL_TRIANGLE_STRIP,
            GL_LINE_STRIP,
    };

    glDrawArrays(drawTypes[shape->getType()], 0, spriteVertexCount);

//    glDisableVertexAttribArray(position);
//    glDisableVertexAttribArray(textureCoords);
}

void RenderVisitor::draw() {
}

} /* namespace jupiter */
