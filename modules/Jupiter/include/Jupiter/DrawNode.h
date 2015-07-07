/*
 * DrawNode.h
 *
 *  Created on: Jul 7, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_DRAWNODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_DRAWNODE_H_

#include "Node.h"

namespace jupiter {

class DrawNode: public Node {
public:
    DrawNode();
    virtual ~DrawNode();

    void bind(Shader* program);

    GLenum getMode() const;
    size_t getCount() const;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_DRAWNODE_H_ */
