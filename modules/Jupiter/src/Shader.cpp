/*
 * ShaderProgram.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: pavel
 */

#include <string>

#include "Jupiter/Tools.h"
#include "Jupiter/Shader.h"

namespace jupiter {

using namespace std;
using namespace glm;

const int INVALID = -1;

void Shader::use() const {
    glUseProgram(_program);
}

Attribute Shader::getAttribute(const std::string& name) const {
    auto attribute = glGetAttribLocation(_program, name.c_str());
    CHECK_GL_ERROR

    jassert(INVALID != attribute, name + " is not an active attribute in shader");
    return Attribute { name, attribute };
}

Uniform Shader::getUniform(const std::string& name) const {
    auto uniform = glGetUniformLocation(_program, name.c_str());
    CHECK_GL_ERROR

    jassert(INVALID != uniform, name + " is not an active uniform in shader");
    return Uniform { name, uniform };
}

GLuint Shader::createProgram(const string& vertexShaderSource, const string& fragmentShaderSource) {
    jassert(!vertexShaderSource.empty(), "vertex shader is empty");
    jassert(!fragmentShaderSource.empty(), "fragment shader is empty");

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource); // TODO surrount shaders to RAII
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint program = glCreateProgram();
    jassert(program, "can't create program");

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus != GL_TRUE) {
        GLint bufLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLen);
        if (bufLen) {
            vector<char> buf(bufLen);
            glGetProgramInfoLog(program, bufLen, NULL, buf.data());
            throw JupiterError(string("can't link shader program\n") + buf.data());
        }
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

GLuint Shader::createShader(GLenum shaderType, const string& source) {
    GLuint shader = glCreateShader(shaderType);
    jassert(shader, "can't create shader");

    const char* sourceBuffer = source.c_str();

    glShaderSource(shader, 1, &sourceBuffer, 0);
    glCompileShader(shader);

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled)
        return shader;

    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    jassert(infoLen, "error in create shader");

    vector<char> buf(infoLen);
    glGetShaderInfoLog(shader, infoLen, 0, buf.data());

//    static array<string, 2> shaderTypeString = { "GL_FRAGMENT_SHADER", "GL_VERTEX_SHADER" };
    static string shaderTypeString[2] = { "GL_FRAGMENT_SHADER", "GL_VERTEX_SHADER" };

    throw JupiterError(""
            "can't create shader " + shaderTypeString[shaderType - GL_FRAGMENT_SHADER] + "\n" + &buf.front());
}

void Shader::setCamera(Camera*) {
}

void Shader::setModel(mat4 const& model) {
}

} /* namespace jupiter */
