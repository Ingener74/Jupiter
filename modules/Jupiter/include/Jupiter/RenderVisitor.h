/*
 * RenderVisitor.h
 *
 *  Created on: Dec 18, 2014
 *      Author: pavel
 */

#ifndef RENDERVISITOR_H_
#define RENDERVISITOR_H_

#include <Jupiter/NodeVisitor.h>

namespace jupiter
{

class Node;

class RenderVisitor: public NodeVisitor
{
public:
    RenderVisitor();
    virtual ~RenderVisitor();

    RenderVisitor& visit(const Node&);
    RenderVisitor& visit(const Sprite&);
};

} /* namespace jupiter */

#endif /* RENDERVISITOR_H_ */
