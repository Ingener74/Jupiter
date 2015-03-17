/*
 * Tools.cpp
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#include <iostream>
#include <sstream>

#include <GL/glew.h>

#include "Jupiter/Tools.h"

namespace jupiter
{

void Tools::glError() throw (JupiterError)
{
    GLenum err = glGetError();
    if (err)
    {
        std::stringstream ss;
        ss << "glGetError: " << std::hex << err << ", " << glGetString(err);
        throw JupiterError(ss.str());
    }
}

} /* namespace ndk_game */

