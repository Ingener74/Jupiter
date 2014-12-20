/*
 * JSONNodeFactory.h
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_JSONNODEFACTORY_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_JSONNODEFACTORY_H_

#include <Jupiter/Builder.h>
#include <Jupiter/Node.h>

namespace jupiter
{

class JSONNodeFactory: public Builder<Node, NodeImpl>::Factory
{
public:
    JSONNodeFactory();
    virtual ~JSONNodeFactory();

    virtual ProductImplPtr create(const std::string&);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_JSONNODEFACTORY_H_ */
