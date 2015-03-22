/*
 * ShaderProgram.h
 *
 *  Created on: Dec 19, 2014
 *      Author: pavel
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#ifdef SWIG
#else
    #include <string>
    #include <memory>

    #include <GL/glew.h>
#endif

namespace jupiter {

class Shader {
public:
    Shader() = default;
    virtual ~Shader() = default;

    virtual void use() const;

    virtual GLint getAttributeLocation(const std::string& name) const;
    virtual GLint getUniformLocation(const std::string& name) const;

protected:
    static GLuint createProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    static GLuint createShader(GLenum shaderType, const std::string& source);

    GLuint _program = 0;
};

} /* namespace jupiter */

#endif /* SHADERPROGRAM_H_ */
