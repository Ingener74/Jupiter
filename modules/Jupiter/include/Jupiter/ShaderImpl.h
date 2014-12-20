/*
 * ShaderImpl.h
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_SHADERIMPL_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_SHADERIMPL_H_

namespace jupiter
{

class ShaderImpl
{
public:
    ShaderImpl();
    ShaderImpl(GLuint _program);
    virtual ~ShaderImpl();

    void use();

protected:
    GLuint _program = 0;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_SHADERIMPL_H_ */
