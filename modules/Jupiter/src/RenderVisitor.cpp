/*
 * RenderVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include <Jupiter/RenderVisitor.h>

namespace jupiter
{

RenderVisitor::RenderVisitor()
{
}

RenderVisitor::~RenderVisitor()
{
}

RenderVisitor& RenderVisitor::visit(const Node&)
{
    return *this;
}

RenderVisitor& RenderVisitor::visit(const Sprite&)
{
    return *this;
}

} /* namespace jupiter */
