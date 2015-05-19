/*
 * KeyboardListener.h
 *
 *  Created on: May 19, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_KEYBOARDLISTENER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_KEYBOARDLISTENER_H_

#ifdef SWIG
    namespace jupiter {
        %feature("director") KeyboardListener;
    }
#else
#endif

#include "Listener.h"

namespace jupiter {

class KeyboardListener: virtual public Listener {
public:

    enum Key{
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    KeyboardListener();
    virtual ~KeyboardListener();

    virtual void key(int keyCode);
    virtual void key(Key);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_KEYBOARDLISTENER_H_ */
