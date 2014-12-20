/*
 * CPPControllerFactory.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#include <Jupiter/CPPControllerFactory.h>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

CPPControllerFactory::CPPControllerFactory()
{
}

CPPControllerFactory::~CPPControllerFactory()
{
}

CPPControllerFactory::ProductImplPtr CPPControllerFactory::create(const std::string& allocator)
{
    throw JupiterError("not implemented");
}

} /* namespace jupiter */
