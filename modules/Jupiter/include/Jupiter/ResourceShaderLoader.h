/*
 * ResourceShaderLoader.h
 *
 *  Created on: Aug 13, 2014
 *      Author: pavel
 */

#ifndef RESOURCESHADERLOADER_H_
#define RESOURCESHADERLOADER_H_

#include <Jupiter/Common.h>
#include <Jupiter/IShaderLoader.h>

namespace jupiter
{

class ResourceShaderLoader: public IShaderLoader
{
public:
	ResourceShaderLoader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	virtual ~ResourceShaderLoader() = default;

	virtual std::string getVertexShader() const;
	virtual std::string getFragmentShader() const;

private:
	std::string _vs, _fs;
};

}  // namespace jupiter

#endif /* RESOURCESHADERLOADER_H_ */
