/*
 * CollisionListener.h
 *
 *  Created on: May 15, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_COLLISIONLISTENER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_COLLISIONLISTENER_H_

#ifdef SWIG
    namespace jupiter {
        %feature("director") CollisionListener;
    }
#else
#endif

#include "Listener.h"

namespace jupiter {

class Body;

class CollisionListener: virtual public Listener {
public:
    CollisionListener();
    virtual ~CollisionListener();

    virtual void collision(Body*);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_COLLISIONLISTENER_H_ */
