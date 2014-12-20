/*
 * JSONGameFactory.h
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_JSONGAMEFACTORY_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_JSONGAMEFACTORY_H_

#include <Jupiter/Builder.h>
#include <Jupiter/Game.h>

namespace jupiter
{

class JSONGameFactory: public Builder<Game, GameImpl>::Factory
{
public:
    JSONGameFactory();
    virtual ~JSONGameFactory();

    virtual ProductImplPtr create(const std::string& game);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_JSONGAMEFACTORY_H_ */
