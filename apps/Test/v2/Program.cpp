/*
 * Program.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: pavel
 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <GL/glew.h>

#include "Shaders.h"
#include "Program.h"

using namespace std;
using namespace glm;

Program::Program(const std::string& vertesShader, const std::string& fragmentShader) {
    program = createProgram(vertesShader, fragmentShader);

    GLint activeAttributes = 0;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &activeAttributes);

    for (GLint i = 0; i < activeAttributes; ++i) {

        const GLsizei bufferSize = 100;

        GLsizei lenght = 0;
        GLint size = 0;
        GLenum type = 0;
        GLchar name[bufferSize];

        glGetActiveAttrib(program, i, bufferSize, &lenght, &size, &type, name);

        attributes.emplace_back(glGetAttribLocation(program, name), name);
    }

    GLint activeUniforms = 0;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUniforms);

    for (GLint i = 0; i < activeUniforms; ++i) {
        const GLsizei bufferSize = 100;

        GLsizei lenght = 0;
        GLint size = 0;
        GLenum type = 0;
        GLchar name[bufferSize];

        glGetActiveUniform(program, i, bufferSize, &lenght, &size, &type, name);

        uniforms.emplace_back(glGetUniformLocation(program, name), name);
    }
}

Program::~Program() {
    glDeleteProgram(program);
}

const Attribute &Program::getAttribute(const std::string &attributeName) const {
    auto it = find_if(attributes.begin(), attributes.end(), [&](const Attribute &i) {
        return i.attributeName == attributeName;
    });
    if (it == attributes.end())
        throw std::runtime_error("no attribute with name " + attributeName);
    return *it;
}

void Program::setUniformMatrix4x4(const std::string& uniformName, const glm::mat4& matrix) {
    auto it = find_if(uniforms.begin(), uniforms.end(), [&](const Uniform& i) {
        return i.uniformName == uniformName;
    });
    if (it == uniforms.end())
        throw std::runtime_error("no uniform");
    glUniformMatrix4fv(it->uniform, 1, GL_FALSE, &matrix[0][0]);
}

std::ostream& operator<<(std::ostream& out, const Program& r) {
    return out << "program id " << r.program << " attributes [ " << [&]() {
        std::stringstream s;
        for(auto i: r.attributes)
        s << i << "; ";
        return s.str();
    }() << "], uniforms [ " << [&]() {
        std::stringstream s;
        for(auto i: r.uniforms)
        s << i << "; ";
        return s.str();
    }() << "]";
}

const Uniform& Program::getUniform(const std::string& uniformName) const {
    auto it = find_if(uniforms.begin(), uniforms.end(), [&](const Uniform& i){
        return i.uniformName == uniformName;
    });
    if(it == uniforms.end())
        throw runtime_error("can't find uniform: " + uniformName);
    return (*it);
}

void Program::setUniform(const std::string& uniformName, GLuint uniformData) {
    throw runtime_error("not implemented yet");
}

void Program::setUniform(GLuint uniformName, GLuint uniformData) {
    throw runtime_error("not implemented yet");
}

void Program::setUniform(const Uniform& uniform, GLuint uniformData) {
    throw runtime_error("not implemented yet");
}
