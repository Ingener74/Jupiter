/*
 * RenderVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include <Jupiter/RenderVisitor.h>
#include <Jupiter/Node.h>
#include <Jupiter/Sprite.h>

namespace jupiter
{

RenderVisitor::RenderVisitor()
{
}

RenderVisitor::RenderVisitor(const glm::mat4& ortho): _ortho(ortho)
{
}

RenderVisitor::~RenderVisitor()
{
}

void jupiter::RenderVisitor::visit(Node* node)
{
    if(!node)
        throw JupiterError("Render visitor: node is nullptr");

    if (node->isVisible())
        for(auto it = node->begin(); it != node->end(); ++it)
            visit(it->node);
}

void jupiter::RenderVisitor::visit(Sprite* sprite)
{
    if(!sprite)
        throw JupiterError("Render visitor: sprite is nullptr");
    /*
     * draw sprite
     */

    if (sprite->isVisible())
    {
        sprite->getProgram()->use();

        sprite->getTexture().bind();

        /*
         * draw shape with program
         */

        for(auto it = sprite->begin(); it != sprite->end(); ++it)
            visit(it->node);
    }
}

} /* namespace jupiter */
