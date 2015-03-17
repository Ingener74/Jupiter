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
}

} /* namespace jupiter */
