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

RenderVisitor::~RenderVisitor()
{
}

RenderVisitor& RenderVisitor::visit( Node& node )
{
    if ( node.isVisible() )
        for ( auto &i : node.getNodes() )
            visit(i.second);
    return *this;
}

RenderVisitor& RenderVisitor::visit( Sprite& sprite )
{
    /*
     * draw sprite
     */

//    sprite._impl->

    /*
     * texture -> bind
     *
     * draw shape with program
     *
     */



    if ( sprite.isVisible() )
        for ( auto i : sprite.getNodes() )
            visit(i.second);
    return *this;
}

} /* namespace jupiter */
