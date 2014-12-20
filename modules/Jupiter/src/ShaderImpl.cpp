/*
 * ShaderImpl.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#include <GL/glew.h>

#include <Jupiter/ShaderImpl.h>
#include <Jupiter/Tools.h>

namespace jupiter
{

ShaderImpl::ShaderImpl()
{
}

ShaderImpl::ShaderImpl( GLuint program ) :
        _program(program)
{
}

ShaderImpl::~ShaderImpl()
{
    glDeleteProgram(_program);
}

void ShaderImpl::use()
{
    glUseProgram(_program);
    Tools::glError();
}

} /* namespace jupiter */
