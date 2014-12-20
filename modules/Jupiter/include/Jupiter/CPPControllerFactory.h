/*
 * CPPControllerFactory.h
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_CPPCONTROLLERFACTORY_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_CPPCONTROLLERFACTORY_H_

#include <Jupiter/Builder.h>
#include <Jupiter/Controller.h>

namespace jupiter
{

class CPPControllerFactory: public Builder<Controller, ControllerImpl>::Factory
{
public:
    CPPControllerFactory();
    virtual ~CPPControllerFactory();

    virtual ProductImplPtr create(const std::string&);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_CPPCONTROLLERFACTORY_H_ */
