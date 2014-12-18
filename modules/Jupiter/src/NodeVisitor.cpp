/*
 * NodeVisitor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#include <Jupiter/NodeVisitor.h>

namespace jupiter
{

NodeVisitor::NodeVisitor()
{
}

NodeVisitor::~NodeVisitor()
{
}

NodeVisitor& NodeVisitor::visit(const Node&)
{
    return *this;
}

NodeVisitor& NodeVisitor::visit(const Sprite&)
{
    return *this;
}

} /* namespace jupiter */
