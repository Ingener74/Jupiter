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

NodeVisitor& NodeVisitor::visit(Node&)
{
    return *this;
}

NodeVisitor& NodeVisitor::visit(Sprite&)
{
    return *this;
}

} /* namespace jupiter */
