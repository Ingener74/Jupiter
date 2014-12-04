/*
 * Tools.cpp
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#include <iostream>
#include <sstream>

#include <GL/glew.h>

#include <Jupiter/Tools.h>

namespace jupiter
{

Tools::Ptr Tools::instance()
{
    static Tools::Ptr self(new Tools);
    return self;
}

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

