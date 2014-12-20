/*
 * FileShaderFactory.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#include <boost/spirit/include/qi.hpp>

#include <Jupiter/FileShaderFactory.h>
#include <Jupiter/ResourceManager.h>
#include <Jupiter/ShaderImpl.h>

#define HERE std::string(__FILE__) + std::string(":") + std::to_string(__LINE__)

namespace jupiter
{

using namespace std;

FileShaderFactory::ProductImplPtr FileShaderFactory::create(const std::string& shader)
{
    namespace q = boost::spirit::qi;

    vector<string> files;

    if (!q::phrase_parse(begin(shader), end(shader), *q::lexeme[+~q::char_(",;")], q::char_(",;"), files))
        throw JupiterError(HERE + " invalid shader " + shader);

    auto vertex = files[0], fragment = files[1];

    auto vertexSource = string{(istreambuf_iterator<char>(*ResourceManager::createResource(vertex))), istreambuf_iterator<char>()},
            fragmentSource = string{(istreambuf_iterator<char>(*ResourceManager::createResource(fragment))), istreambuf_iterator<char>()};

    return make_shared<ShaderImpl>(createProgram(vertexSource, fragmentSource));
}

GLuint FileShaderFactory::createProgram(string vertexShaderSource, string fragmentShaderSource)
{
    if (vertexShaderSource.empty()) throw JupiterError("vertex shader is empty");
    if (fragmentShaderSource.empty()) throw JupiterError("fragment shader is empty");

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource); // TODO surrount shaders to RAII
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint program = glCreateProgram();
    if (!program) throw JupiterError("can't create program");

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus != GL_TRUE)
    {
        GLint bufLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLen);
        if (bufLen)
        {
            vector<char> buf(bufLen);
            glGetProgramInfoLog(program, bufLen, NULL, &buf.front());
            throw JupiterError(string("can't link shader program\n") + &buf.front());
        }
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

GLuint FileShaderFactory::createShader(GLenum shaderType, string source)
{
    GLuint shader = glCreateShader(shaderType);
    if (!shader) throw JupiterError("can't create shader");

    const char* source_buffer = source.c_str();

    glShaderSource(shader, 1, &source_buffer, 0);
    glCompileShader(shader);

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled) return shader;

    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    if (!infoLen) throw JupiterError("error in create shader");

    vector<char> buf(infoLen);
    glGetShaderInfoLog(shader, infoLen, 0, &buf.front());

    static array<string, 2> shaderTypeString =
    { "GL_FRAGMENT_SHADER", "GL_VERTEX_SHADER" };

    throw JupiterError(""
            "can't create shader " + shaderTypeString[shaderType - GL_FRAGMENT_SHADER] + "\n" + &buf.front());
}

} /* namespace jupiter */
