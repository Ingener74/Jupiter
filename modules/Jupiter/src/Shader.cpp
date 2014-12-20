/*
 * ShaderProgram.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: pavel
 */

#include <Jupiter/Shader.h>
#include <Jupiter/ShaderImpl.h>
#include <Jupiter/Builder.h>

namespace jupiter
{

Shader::Shader()
{
}

Shader::Shader(const std::string& program) :
        _impl(Builder<Shader, ShaderImpl>::create(program))
{
}

Shader::~Shader()
{
}

void Shader::use() const
{
    if (_impl)
        _impl->use();
}

} /* namespace jupiter */
