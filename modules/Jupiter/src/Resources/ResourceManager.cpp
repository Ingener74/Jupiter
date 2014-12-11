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

    return reg.back()->createResource(pathPrefix() + "/" + filename);
}

void ResourceManager::setFactory(shared_ptr<Factory> factory)
{
    Register().push_back(factory);
}

list<shared_ptr<ResourceManager::Factory>>& ResourceManager::Register()
{
	static list<shared_ptr<Factory>> factoryStack;
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

