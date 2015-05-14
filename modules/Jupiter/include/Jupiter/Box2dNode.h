/*
 * Box2dNode.h
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_BOX2DNODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_BOX2DNODE_H_

#include "Node.h"

class b2Body;

namespace jupiter {

class Box2DVisitor;

class Box2dNode: virtual public Node {
public:
    Box2dNode(Box2DVisitor*);
    virtual ~Box2dNode();

private:
    b2Body* _body = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_BOX2DNODE_H_ */
