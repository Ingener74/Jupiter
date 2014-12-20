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

void RenderVisitor::visit(Node& node)
{
    if (node.isVisible())
        for (auto &i : node.getNodes())
            visit(i.second);
}

void RenderVisitor::visit(Sprite& sprite)
{
    /*
     * draw sprite
     */

    if (sprite.isVisible())
    {
        sprite.getProgram().use();

        sprite.getTexture().bind();

        /*
         * draw shape with program
         *
         */


        for (auto i : sprite.getNodes())
            visit(i.second);
    }
}

} /* namespace jupiter */
