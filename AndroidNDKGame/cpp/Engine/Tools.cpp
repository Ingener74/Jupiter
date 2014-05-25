/*
 * Tools.cpp
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#include "Tools.h"

namespace ndk_game
{

Tools::Tools()
{
}

Tools::~Tools()
{
}

void Tools::glError() throw (std::runtime_error)
{
    GLenum err = glGetError();
    if(err){
        std::stringstream ss;
        ss << "glGetError: " << std::hex << err << ", "<< glGetString(err);
        throw std::runtime_error(ss.str());
    }
}

} /* namespace ndk_game */
