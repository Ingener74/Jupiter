/*
 * PrintVisitor.h
 *
 *  Created on: Mar 25, 2015
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_PRINTVISITOR_H_
#define MODULES_JUPITER_INCLUDE_PRINTVISITOR_H_

#ifdef SWIG
#else
    #include "Ref.h"
#endif

#include "NodeVisitor.h"

namespace jupiter {

class Game;

class PrintVisitor: public NodeVisitor {
public:
    PrintVisitor(Game*);
    virtual ~PrintVisitor();

    virtual void begin();
    virtual void end();

private:
    Game* _game = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_PRINTVISITOR_H_ */
