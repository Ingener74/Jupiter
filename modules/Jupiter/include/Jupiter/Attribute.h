/*
 * Attribute.h
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_ATTRIBUTE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_ATTRIBUTE_H_

#ifdef SWIG
#else
    #include <string>
    #if defined(ANDROID)
        #include <GLES2/gl2.h>
    #elif defined(__APPLE__)
		#include <OpenGL/gl.h>
	#else
		#include <GL/gl.h>
    #endif
#endif

namespace jupiter {

class Attribute {
public:
    Attribute(const std::string& name, int attribute);
    virtual ~Attribute();

    void set(class Shape* shape);

private:
    std::string name;
    int attribute;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_ATTRIBUTE_H_ */
