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

#ifdef ANDROID
    #include <GLES2/gl2.h>
#else
    #include <GL/glew.h>
#endif

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Jupiter/Tools.h"

namespace jupiter
{

using namespace std;
using namespace glm;

void Tools::glError(const std::string& file, int line, const std::string& function)
{
    GLenum err = glGetError();
    if (err)
    {
        std::stringstream ss;
        ss <<
            (file.empty()       ? "" : file            ) << ":" <<
            (-1 == line         ? "" : to_string(line) ) << ":" << // � MinGW ��� to_string, ����� ���������
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

ostream& operator<<(ostream& out, const mat4& r){
    auto t = transpose(r);
    return out << endl <<
        "[" << setw(10) << t[0][0] << ", " << setw(10) << t[0][1] << ", " << setw(10) << t[0][2] << ", " << setw(10) << t[0][3] << ";" << endl <<
        " " << setw(10) << t[1][0] << ", " << setw(10) << t[1][1] << ", " << setw(10) << t[1][2] << ", " << setw(10) << t[1][3] << ";" << endl <<
        " " << setw(10) << t[2][0] << ", " << setw(10) << t[2][1] << ", " << setw(10) << t[2][2] << ", " << setw(10) << t[2][3] << ";" << endl <<
        " " << setw(10) << t[3][0] << ", " << setw(10) << t[3][1] << ", " << setw(10) << t[3][2] << ", " << setw(10) << t[3][3] << "]" << endl;
}

std::ostream& operator <<(std::ostream& out, const glm::vec3& r) {
    return out << "[" << r.x << ", " << r.y << ", " << r.z << "]";
}

std::ostream& operator <<(std::ostream& out, const glm::quat& r) {
    return out << "[" << r.x << ", " << r.y << ", " << r.z << ", " << r.w << "]";
}

} /* namespace jupiter */
