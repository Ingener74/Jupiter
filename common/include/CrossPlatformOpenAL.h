/*
 * CrossPlatformOpenAL.h
 *
 *  Created on: Oct 26, 2015
 *      Author: pavel
 */

#ifndef COMMON_INCLUDE_CROSSPLATFORMOPENAL_H_
#define COMMON_INCLUDE_CROSSPLATFORMOPENAL_H_

#if defined(__APPLE__)
    #include <OpenAL/al.h>
    #include <OpenAL/alc.h>
#else
    #include <AL/al.h>
    #include <AL/alc.h>
#endif

#endif /* COMMON_INCLUDE_CROSSPLATFORMOPENAL_H_ */
