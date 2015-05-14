/*
 * Listener.h
 *
 *  Created on: May 14, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_LISTENER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_LISTENER_H_

#ifdef SWIG
    namespace jupiter {
        #pragma SWIG nowarn=473
        %feature("director") Listener;
    }
#else
#endif

namespace jupiter {

class Node;

class Listener {
public:
    Listener();
    virtual ~Listener();

    virtual Node* getNode();
    virtual Listener* setNode(Node*);

private:
    Node* _node = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_LISTENER_H_ */
