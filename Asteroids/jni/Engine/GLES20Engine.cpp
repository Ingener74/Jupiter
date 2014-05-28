/*
 * GLES20Engine.cpp
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#include <Engine/GLES20Engine.h>
#include <Engine/Log.h>

namespace ndk_game
{

GLES20Engine::GLES20Engine(IShaderLoader::Ptr sl)
{
    _program = createProgram(sl->getVertexShader(), sl->getFragmentShader());
}

GLES20Engine::~GLES20Engine()
{
    glDeleteProgram(_program);
    glDeleteShader(_vs);
    glDeleteShader(_fs);
}

void GLES20Engine::draw(Scene::Ptr) throw (std::runtime_error)
{
}

GLuint GLES20Engine::createShader(GLenum shaderType, const char* source)
{
    Log() << "Create shader";

    GLuint shader = glCreateShader(shaderType);
    if (!shader) throw std::runtime_error("can't create shader");

    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled) return shader;

    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    if (!infoLen) throw std::runtime_error("error in create shader");

    std::unique_ptr<char> buf(new char[infoLen]);
    glGetShaderInfoLog(shader, infoLen, 0, buf.get());

    throw std::runtime_error(buf.get());
}

GLuint GLES20Engine::createProgram(const char* vertexShader,
        const char* fragmentShader)
{
    Log() << "Create program";

    _vs = createShader(GL_VERTEX_SHADER, vertexShader);
    _fs = createShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLuint program = glCreateProgram();
    if (!program) throw std::runtime_error("can't create program");

    glAttachShader(program, _vs);
    glAttachShader(program, _fs);

    glLinkProgram(program);
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus != GL_TRUE)
    {
        GLint bufLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLen);
        if (bufLen)
        {
            std::unique_ptr<char> buf(new char[bufLen]);
            glGetProgramInfoLog(program, bufLen, NULL, buf.get());
            throw std::runtime_error(buf.get());
        }
    }
    return program;
}

} /* namespace ndk_game */
