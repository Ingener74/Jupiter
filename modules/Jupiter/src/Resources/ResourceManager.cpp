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

std::shared_ptr<ResourceManager> ResourceManager::instance()
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

void ResourceManager::pushResourceFactory(std::shared_ptr<IFactory> factory)
{
    Register().push_back(factory);
}

ResourceManager::ResourceManager()
{
}

list<std::shared_ptr<ResourceManager::IFactory>>& ResourceManager::Register()
{
	static list<std::shared_ptr<IFactory>> factoryStack;
	return factoryStack;
}

void ResourceManager::popResourceFactory()
{
	if (Register().size() < 2) return;
	Register().pop_back();
}

} /* namespace jupiter */
