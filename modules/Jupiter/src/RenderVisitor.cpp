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

    sprite->getProgram()->use();

    sprite->getTexture()->bind();

    /*
     * draw shape with program
     */
//    glUniform1i(_uTEX, 0);
//    glEnableVertexAttribArray(_aPOS);
//    glEnableVertexAttribArray(_aTEX);
//
//    const GLfloat * spriteVertex = s->getVertex();
//    uint32_t spriteVertexCount = s->getVertexCount();
//
//    glVertexAttribPointer(_aPOS, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &spriteVertex[0]);
//    glVertexAttribPointer(_aTEX, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &spriteVertex[3]);
//
//    glm::mat4 mvp = _ortho * s->getModelMatrix();
//
//    glUniformMatrix4fv(_uMVP, 1, GL_FALSE, glm::value_ptr(mvp));
//
//    GLenum drawType;
//    switch (s->getDrawType())
//    {
//    case ISpriteLoader::SpriteType::Triangles:
//        drawType = GL_TRIANGLES;
//        break;
//    case ISpriteLoader::SpriteType::TriangleFan:
//        drawType = GL_TRIANGLE_FAN;
//        break;
//    case ISpriteLoader::SpriteType::TriangleStrip:
//        drawType = GL_TRIANGLE_STRIP;
//        break;
//    case ISpriteLoader::SpriteType::LineStrip:
//        drawType = GL_LINE_STRIP;
//        break;
//    default:
//        break;
//    }
//    glDrawArrays(drawType, 0, spriteVertexCount);
//
//    glDisableVertexAttribArray(_aPOS);
//    glDisableVertexAttribArray(_aTEX);
}

} /* namespace jupiter */
