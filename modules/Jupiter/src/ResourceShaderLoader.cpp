/*
 * ResourceShaderLoader.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: pavel
 */

#include <Jupiter/ResourceManager.h>
#include <Jupiter/ResourceShaderLoader.h>

namespace jupiter
{

using namespace std;

ResourceShaderLoader::ResourceShaderLoader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) :
		_vs(vertexShaderPath), _fs(fragmentShaderPath)
{
}

string ResourceShaderLoader::getVertexShader() const
{
	auto file = ResourceManager::createResource(_vs);
	return string((istreambuf_iterator<char>(*file)), istreambuf_iterator<char>());
}

string ResourceShaderLoader::getFragmentShader() const
{
	auto file = ResourceManager::createResource(_fs);
	return string((istreambuf_iterator<char>(*file)), istreambuf_iterator<char>());
}

}  // namespace jupiter

