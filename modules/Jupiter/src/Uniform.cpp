/*
 * Uniform.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

#ifndef ANDROID
    #include <GL/glew.h>
#endif

#include <iostream>
#include "Jupiter/Tools.h"
#include "Jupiter/Texture.h"
#include "Jupiter/Uniform.h"

namespace jupiter {

Uniform::Uniform(const std::string& name, int uniform) :
        name(name), uniform(uniform) {
}

Uniform::~Uniform() {
}

void Uniform::set(int v0) {
    glUniform1i(uniform, v0);
    CHECK_GL_ERROR
}

void Uniform::set(int v0, int v1) {
    glUniform2i(uniform, v0, v1);
    CHECK_GL_ERROR
}

void Uniform::set(int v0, int v1, int v2) {
    glUniform3i(uniform, v0, v1, v2);
    CHECK_GL_ERROR
}

void Uniform::set(int v0, int v1, int v2, int v3) {
    glUniform4i(uniform, v0, v1, v2, v3);
    CHECK_GL_ERROR
}

void Uniform::set(float v0) {
    glUniform1f(uniform, v0);
    CHECK_GL_ERROR
}

void Uniform::set(float v0, float v1) {
    glUniform2f(uniform, v0, v1);
    CHECK_GL_ERROR
}

void Uniform::set(float v0, float v1, float v2) {
    glUniform3f(uniform, v0, v1, v2);
    CHECK_GL_ERROR
}

void Uniform::set(float v0, float v1, float v2, float v3) {
    glUniform4f(uniform, v0, v1, v2, v3);
    CHECK_GL_ERROR
}

void Uniform::set(const Texture* texture) {
    // glUniform1i(uniform, texture->textureID);
    throw JupiterError("not implemented");
    CHECK_GL_ERROR
}

void Uniform::set(const glm::mat4x4& matrix, bool transpose) {
    glUniformMatrix4fv(uniform, 1, transpose, glm::value_ptr(matrix));
    CHECK_GL_ERROR
}

} /* namespace jupiter */
