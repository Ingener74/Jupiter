/*
 * MoveListener.h
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_MOVELISTENER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_MOVELISTENER_H_

#ifdef SWIG
    namespace jupiter {
        %feature("director") MoveListener;
    }
#else
#endif

#include "Listener.h"

namespace jupiter {

class MoveListener: virtual public Listener {
public:
    MoveListener();
    virtual ~MoveListener();

    virtual void move(float x, float y, float z);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_MOVELISTENER_H_ */
