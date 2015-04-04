/*
 * Tools.h
 *
 *  Created on: Apr 2, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_TOOLS_H_
#define APPS_TEST_TOOLS_H_

#include <iostream>
#include <glm/glm.hpp>

using glm::mat4;
using std::ostream;

ostream& operator<<(ostream& out, const mat4& r);

size_t upperPowerOfTwo(size_t v);

struct Texture{
    GLuint textureId = 0;
    size_t textureWidth = 0,
            textureHeight = 0;
    size_t width = 0,
            height = 0;
};

Texture loadTexture(const std::string& fileName);

#endif /* APPS_TEST_TOOLS_H_ */
