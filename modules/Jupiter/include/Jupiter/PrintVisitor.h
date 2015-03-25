/*
 * PrintVisitor.h
 *
 *  Created on: Mar 25, 2015
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_PRINTVISITOR_H_
#define MODULES_JUPITER_INCLUDE_PRINTVISITOR_H_

#include "NodeVisitor.h"

namespace jupiter {

class PrintVisitor: public NodeVisitor {
public:
    PrintVisitor();
    virtual ~PrintVisitor();

    virtual void begin();

    virtual void visit(Node*);
    virtual void visit(Sprite*);

    virtual void end();

private:
    int calcTabs(Node*);
    std::string tabs(int);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_PRINTVISITOR_H_ */
