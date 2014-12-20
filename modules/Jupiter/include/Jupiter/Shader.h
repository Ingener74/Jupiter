/*
 * ShaderProgram.h
 *
 *  Created on: Dec 19, 2014
 *      Author: pavel
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <string>
#include <memory>

#include <GL/glew.h>

namespace jupiter
{

class ShaderImpl;

class Shader
{
public:
    Shader();
    Shader(const std::string& program);
    virtual ~Shader();

    void use() const;

private:
    std::shared_ptr<ShaderImpl> _impl;
};

} /* namespace jupiter */

#endif /* SHADERPROGRAM_H_ */
