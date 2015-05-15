/*
 * ScaleListener.h
 *
 *  Created on: May 15, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_SCALELISTENER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_SCALELISTENER_H_

#ifdef SWIG
    namespace jupiter {
        %feature("director") ScaleListener;
    }
#else
#endif

#include "Listener.h"

namespace jupiter {

class ScaleListener: virtual public Listener {
public:
    ScaleListener();
    virtual ~ScaleListener();

    virtual void scale(float x, float y, float z);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_SCALELISTENER_H_ */
