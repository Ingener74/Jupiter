/*
 * ShaderProgram.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: pavel
 */

#include <string>
#include "Jupiter/Shader.h"
#include "Jupiter/Builder.h"

namespace jupiter {

using namespace std;

void Shader::use() const {
    glUseProgram(_program);
}

GLint Shader::getAttributeLocation(const std::string& name) const {
    return glGetAttribLocation(_program, name.c_str());
}

GLint Shader::getUniformLocation(const string& name) const {
    return glGetUniformLocation(_program, name.c_str());
}

GLuint Shader::createProgram(const string& vertexShaderSource, const string& fragmentShaderSource) {
    if (vertexShaderSource.empty())
        throw JupiterError("vertex shader is empty");
    if (fragmentShaderSource.empty())
        throw JupiterError("fragment shader is empty");

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource); // TODO surrount shaders to RAII
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint program = glCreateProgram();
    if (!program)
        throw JupiterError("can't create program");

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
    if (!shader)
        throw JupiterError("can't create shader");

    const char* sourceBuffer = source.c_str();

    glShaderSource(shader, 1, &sourceBuffer, 0);
    glCompileShader(shader);

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled)
        return shader;

    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    if (!infoLen)
        throw JupiterError("error in create shader");

    vector<char> buf(infoLen);
    glGetShaderInfoLog(shader, infoLen, 0, buf.data());

    static array<string, 2> shaderTypeString = { "GL_FRAGMENT_SHADER", "GL_VERTEX_SHADER" };

    throw JupiterError(""
            "can't create shader " + shaderTypeString[shaderType - GL_FRAGMENT_SHADER] + "\n" + &buf.front());
}

} /* namespace jupiter */

