/*
 * CrossPlatformOpenGL.h
 *
 *  Created on: Oct 26, 2015
 *      Author: pavel
 */

#ifndef COMMON_INCLUDE_CROSSPLATFORMOPENGL_H_
#define COMMON_INCLUDE_CROSSPLATFORMOPENGL_H_

#if defined(ANDROID)
    #include <GLES2/gl2.h>
#elif defined(__APPLE__)
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#endif /* COMMON_INCLUDE_CROSSPLATFORMOPENGL_H_ */
