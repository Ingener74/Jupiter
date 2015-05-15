/*
 * CollisionListener.h
 *
 *  Created on: May 15, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_COLLISIONLISTENER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_COLLISIONLISTENER_H_

#include "Listener.h"

namespace jupiter {

class Node;

class CollisionListener: virtual public Listener {
public:
    CollisionListener();
    virtual ~CollisionListener();

    virtual void collision(Node*);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_COLLISIONLISTENER_H_ */
