/*
 * Attribute.h
 *
 *  Created on: Apr 14, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_V2_ATTRIBUTE_H_
#define APPS_TEST_V2_ATTRIBUTE_H_

#include <string>
#if defined(__APPLE__)
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

class Attribute {
public:
    Attribute(GLint attribute = 0, std::string attributeName = { });

    GLint attribute = 0;
    std::string attributeName;

    friend std::ostream& operator <<(std::ostream& out, const Attribute& r);
};

#endif /* APPS_TEST_V2_ATTRIBUTE_H_ */
