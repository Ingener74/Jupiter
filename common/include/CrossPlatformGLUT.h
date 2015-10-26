/*
 * CrossPlatformGLUT.h
 *
 *  Created on: Oct 26, 2015
 *      Author: pavel
 */

#ifndef COMMON_INCLUDE_CROSSPLATFORMGLUT_H_
#define COMMON_INCLUDE_CROSSPLATFORMGLUT_H_

#ifdef EMSCRIPTEN
    #include <GL/glut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#endif /* COMMON_INCLUDE_CROSSPLATFORMGLUT_H_ */
