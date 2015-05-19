/*
 * RotationListener.h
 *
 *  Created on: May 19, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_ROTATIONLISTENER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_ROTATIONLISTENER_H_

#ifdef SWIG
    namespace jupiter {
        %feature("director") RotationListener;
    }
#else
#endif

#include "Listener.h"

namespace jupiter {

class RotationListener: virtual public Listener {
public:
    RotationListener();
    virtual ~RotationListener();

    virtual void rotate(float x, float y, float z, float angle);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_ROTATIONLISTENER_H_ */
