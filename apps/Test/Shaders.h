/*
 * Shaders.h
 *
 *  Created on: Apr 1, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_SHADERS_H_
#define APPS_TEST_SHADERS_H_

#include <string>

GLuint createShader(GLenum shaderType, const std::string& source);
GLuint createProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

#endif /* APPS_TEST_SHADERS_H_ */
