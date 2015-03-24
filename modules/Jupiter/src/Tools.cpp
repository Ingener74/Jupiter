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

using namespace std;

void Tools::glError(const std::string& file, int line, const std::string& function) throw (JupiterError)
{
    GLenum err = glGetError();
    if (err)
    {
        std::stringstream ss;
        ss <<
            (file.empty()       ? "" : file            ) << ":" <<
            (-1 == line         ? "" : to_string(line) ) << ":" <<
            (function.empty()   ? "" : function        ) <<
            ":glGetError: " << std::hex << err << ", " << glGetString(err);
        throw JupiterError(ss.str());
    }
}

} /* namespace ndk_game */

