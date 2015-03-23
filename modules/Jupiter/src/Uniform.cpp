/*
 * Uniform.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

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
}

void Uniform::set(int v0, int v1) {
    glUniform2i(uniform, v0, v1);
}

void Uniform::set(int v0, int v1, int v2) {
    glUniform3i(uniform, v0, v1, v2);
}

void Uniform::set(int v0, int v1, int v2, int v3) {
    glUniform4i(uniform, v0, v1, v2, v3);
}

void Uniform::set(float v0) {
    glUniform1f(uniform, v0);
}

void Uniform::set(float v0, float v1) {
    glUniform2f(uniform, v0, v1);
}

void Uniform::set(float v0, float v1, float v2) {
    glUniform3f(uniform, v0, v1, v2);
}

void Uniform::set(float v0, float v1, float v2, float v3) {
    glUniform4f(uniform, v0, v1, v2, v3);
}

void Uniform::set(const Texture* texture) {
    glUniform1i(uniform, texture->textureID);
}

void Uniform::set(const glm::mat4x4& matrix, bool transpose) {
    glUniformMatrix4fv(uniform, 1, transpose, glm::value_ptr(matrix));
}

} /* namespace jupiter */
