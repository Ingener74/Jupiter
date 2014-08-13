/*
 * ResourceManager.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: pavel
 */

#include <Jupiter/ResourceManager.h>

namespace jupiter
{

using namespace std;

ResourceManager::Ptr ResourceManager::instance()
{
	static shared_ptr<ResourceManager> self(new ResourceManager);
	return self;
}

ResourceManager::~ResourceManager()
{
}

ResourceManager::Resource ResourceManager::createResource(const string& filename)
{
	return Register().back()->createResource(filename);
}

void ResourceManager::pushResourceFactory(IFactory::Ptr factory)
{
    Register().push_back(factory);
}

ResourceManager::ResourceManager()
{
}

list<ResourceManager::IFactory::Ptr>& ResourceManager::Register()
{
	static list<IFactory::Ptr> factoryStack;
	return factoryStack;
}

void ResourceManager::popResourceFactory()
{
	if (Register().size() < 2) return;
	Register().pop_back();
}

} /* namespace jupiter */
