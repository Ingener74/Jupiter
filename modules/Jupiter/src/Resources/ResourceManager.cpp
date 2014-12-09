/*
 * ResourceManager.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: pavel
 */

#include <Jupiter/ResourceManager.h>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

using namespace std;

ResourceManager::Resource ResourceManager::createResource(const string& filename)
{
    auto reg = Register();
    if(reg.empty())
        throw JupiterError("have no resource factories");
	return reg.back()->createResource(filename);
}

void ResourceManager::pushResourceFactory(shared_ptr<IFactory> factory)
{
    Register().push_back(factory);
}

void ResourceManager::popResourceFactory()
{
	Register().pop_back();
}

list<shared_ptr<ResourceManager::IFactory>>& ResourceManager::Register()
{
	static list<shared_ptr<IFactory>> factoryStack;
	return factoryStack;
}

string jupiter::ResourceManager::pathPrefix()
{
    return PathPrefix();
}

void jupiter::ResourceManager::setPathPrefix( const string& pathPrefix )
{
    PathPrefix() = pathPrefix;
}

string& jupiter::ResourceManager::PathPrefix()
{
    static string pathPrefix;
    return pathPrefix;
}

} /* namespace jupiter */

