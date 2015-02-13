/*
 * ShaderProgram.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: pavel
 */

#include "Jupiter/Shader.h"
#include "Jupiter/Builder.h"

namespace jupiter
{

void Shader::use() const
{
    glUseProgram(_program);
}

} /* namespace jupiter */
