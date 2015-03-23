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

    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/gtc/type_ptr.hpp>
    #include <glm/gtc/matrix_transform.hpp>
#endif

#include "Jupiter/Shape.h"
#include "Jupiter/Texture.h"

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

    void set(class Shape* shape);

private:
    std::string name;
    int attribute;
};

class Uniform {
public:
    Uniform(const std::string& name, int uniform) :
            name(name), uniform(uniform) {
    }
    virtual ~Uniform() {
    }

    void set(int data) {
        glUniform1i(uniform, data);
    }

    void set(const glm::mat4x4& matrix, bool transpose = false) {
        glUniformMatrix4fv(uniform, 1, transpose, glm::value_ptr(matrix));
    }

    void set(const Texture* texture){
        glUniform1i(uniform, texture->textureID);
    }

private:
    std::string name;
    int uniform;
};

class Shader {
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

inline void Attribute::set(class Shape* shape) {
    auto component = shape->getComponent(name);
    glVertexAttribPointer(attribute, component.getSize(), GL_FLOAT, GL_FALSE, shape->getStride(),
            component.getOffset());
}

}
/* namespace jupiter */

#endif /* SHADERPROGRAM_H_ */
