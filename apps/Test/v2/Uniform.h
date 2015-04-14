/*
 * Uniform.h
 *
 *  Created on: Apr 14, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_V2_UNIFORM_H_
#define APPS_TEST_V2_UNIFORM_H_

#include <string>

#include <GL/gl.h>

class Uniform {
public:
    Uniform(GLint uniform = 0, std::string uniformName = { });
    GLint uniform = 0;
    std::string uniformName;

    friend std::ostream& operator <<(std::ostream& out, const Uniform& r);
};

#endif /* APPS_TEST_V2_UNIFORM_H_ */
