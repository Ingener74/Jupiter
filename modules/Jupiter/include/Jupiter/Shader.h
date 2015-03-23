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

class Attribute {
public:
    Attribute(const std::string& name, int attribute) :
        name(name), attribute(attribute) {
        glEnableVertexAttribArray(attribute);
    }
    virtual ~Attribute() {
        glDisableVertexAttribArray(attribute);
    }

    void setData(class Shape* shape) {
        auto component = shape->getComponent(name);
        glVertexAttribPointer(attribute, component.getSize(), GL_FLOAT, GL_FALSE, shape->getStride(), component.getOffset());
    }

private:
    std::string name;
    int attribute;
};

class Uniform {
public:
    Uniform(){
    }
    virtual ~Uniform(){
    }

private:
};

class Shader {
    const static int INVALID = -1;

public:
    Shader() = default;
    virtual ~Shader() = default;

    virtual void use() const;

    Attribute getAttribute(const std::string& name) const;
    Uniform getUniform(const std::string& name) const;

protected:
    static GLuint createProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    static GLuint createShader(GLenum shaderType, const std::string& source);

    GLuint _program = 0;
};

} /* namespace jupiter */

#endif /* SHADERPROGRAM_H_ */
