/*
 * Tools.cpp
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include <GL/glew.h>

#include "Jupiter/Tools.h"

namespace jupiter
{

using namespace std;

void Tools::glError(const std::string& file, int line, const std::string& function)
{
    GLenum err = glGetError();
    if (err)
    {
        std::stringstream ss;
        ss <<
            (file.empty()       ? "" : file            ) << ":" <<
            (-1 == line         ? "" : to_string(line) ) << ":" << // в MinGW нет to_string
            (function.empty()   ? "" : function        ) <<
            ":glGetError: " << std::hex << err << ", " << glGetString(err);
        throw JupiterError(ss.str());
    }
}

uint32_t Tools::upperPowerOfTwo(uint32_t v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

} /* namespace ndk_game */

