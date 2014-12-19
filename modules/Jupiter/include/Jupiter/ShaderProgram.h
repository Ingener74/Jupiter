/*
 * ShaderProgram.h
 *
 *  Created on: Dec 19, 2014
 *      Author: pavel
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <string>

namespace jupiter
{

class ShaderProgram
{
public:
    ShaderProgram();
    ShaderProgram(const std::string& program);
    virtual ~ShaderProgram();

    void use() const;

private:
};

} /* namespace jupiter */

#endif /* SHADERPROGRAM_H_ */
