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

class Shader
{
public:
    Shader() = default;
    virtual ~Shader() = default;

    virtual void use() const;

private:
    GLuint _program = 0;
};

} /* namespace jupiter */

#endif /* SHADERPROGRAM_H_ */
