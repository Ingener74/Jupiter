/*
 * Shaders.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: pavel
 */

#include <array>
#include <vector>

#include <GL/glew.h>

#include "Shaders.h"

using namespace std;

GLuint createProgram(const string& vertexShaderSource, const string& fragmentShaderSource) {
    if (vertexShaderSource.empty())
        throw runtime_error("vertex shader is empty");
    if (fragmentShaderSource.empty())
        throw runtime_error("fragment shader is empty");

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint program = glCreateProgram();
    if (!program)
        throw runtime_error("can't create program");

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
            throw runtime_error(string("can't link shader program\n") + buf.data());
        }
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

GLuint createShader(GLenum shaderType, const string& source) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader)
        throw runtime_error("can't create shader");

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
        throw runtime_error("error in create shader");

    vector<char> buf(infoLen);
    glGetShaderInfoLog(shader, infoLen, 0, buf.data());

    static array<string, 2> shaderTypeString = { "GL_FRAGMENT_SHADER", "GL_VERTEX_SHADER" };

    throw runtime_error(""
            "can't create shader " + shaderTypeString[shaderType - GL_FRAGMENT_SHADER] + "\n" + &buf.front());
}
