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

#include "RCO.h"
#include "Shape.h"
#include "Texture.h"
#include "Attribute.h"
#include "Uniform.h"

namespace jupiter {

class Camera;

class Shader: virtual public RCO{
public:
    enum class CameraPins {
        PROJECTION, VIEW
    };

    enum class Pins {
        PROJECTION, VIEW, MODEL
    };

    Shader() = default;
    virtual ~Shader() = default;

    virtual void use() const;

    Attribute getAttribute(const std::string& name) const;
    Uniform getUniform(const std::string& name) const;

    void setCamera(Camera*);
    void setModel(glm::mat4 const&);

protected:
    static GLuint createProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    static GLuint createShader(GLenum shaderType, const std::string& source);

    GLuint _program = 0;
};

}
/* namespace jupiter */

#endif /* SHADERPROGRAM_H_ */
