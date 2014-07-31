/*
 * Tools.cpp
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#include <Jupiter/Tools.h>

namespace ndk_game
{

Tools::Ptr ndk_game::Tools::instance()
{
    static Tools::Ptr self(new Tools);
    return self;
}

void Tools::glError() throw (std::runtime_error)
{
    GLenum err = glGetError();
    if (err)
    {
        std::stringstream ss;
        ss << "glGetError: " << std::hex << err << ", " << glGetString(err);
        throw std::runtime_error(ss.str());
    }
}

Tools::Tools()
{
}

} /* namespace ndk_game */

