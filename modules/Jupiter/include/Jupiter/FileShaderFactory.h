/*
 * FileShaderFactory.h
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_FILESHADERFACTORY_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_FILESHADERFACTORY_H_

#include <Jupiter/Builder.h>
#include <Jupiter/Shader.h>

namespace jupiter
{

class FileShaderFactory: public Builder<Shader, ShaderImpl>::Factory
{
public:
    virtual ~FileShaderFactory() = default;
    virtual ProductImplPtr create(const std::string&);

private:
    static GLuint createProgram(std::string vertexShader, std::string fragmentShader);
    static GLuint createShader(GLenum shaderType, std::string source);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_FILESHADERFACTORY_H_ */
