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

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourceManager::Resource ResourceManager::createResource(const std::string& filename)
{
	return make_shared<Resource>;
}

} /* namespace jupiter */
