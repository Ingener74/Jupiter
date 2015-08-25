/*
 * Tools.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: pavel
 */

#include <iomanip>
#include <stdexcept>

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "lodepng.h"

#include "Tools.h"

using namespace std;
using namespace glm;

ostream& operator<<(ostream& out, const mat4& r){
    auto t = transpose(r);
    return out << endl <<
        "[" << setw(10) << t[0][0] << ", " << setw(10) << t[0][1] << ", " << setw(10) << t[0][2] << ", " << setw(10) << t[0][3] << ";" << endl <<
        " " << setw(10) << t[1][0] << ", " << setw(10) << t[1][1] << ", " << setw(10) << t[1][2] << ", " << setw(10) << t[1][3] << ";" << endl <<
        " " << setw(10) << t[2][0] << ", " << setw(10) << t[2][1] << ", " << setw(10) << t[2][2] << ", " << setw(10) << t[2][3] << ";" << endl <<
        " " << setw(10) << t[3][0] << ", " << setw(10) << t[3][1] << ", " << setw(10) << t[3][2] << ", " << setw(10) << t[3][3] << "]" << endl;
}

size_t upperPowerOfTwo(size_t v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

Texture loadTexture(const std::string& fileName) {

    cout << __PRETTY_FUNCTION__ << endl;

    Texture result;

    vector<uint8_t> data;
    unsigned w, h;
    cout << __PRETTY_FUNCTION__ << endl;
    auto error = lodepng::decode(data, w, h, fileName, LCT_RGBA);
    cout << __PRETTY_FUNCTION__ << lodepng_error_text(error)<< endl;
    if (error)
        throw runtime_error(lodepng_error_text(error));
    cout << __PRETTY_FUNCTION__ << endl;

    result.width = w;
    result.height = h;

    auto lenght = std::max(result.width, result.height);

    result.textureWidth = upperPowerOfTwo(lenght);
    result.textureHeight = upperPowerOfTwo(lenght);

//    cout << "image loaded: " << result.width << " x " << result.height << ", texture: " << result.textureWidth << " x " << result.textureHeight << endl;

    glGenTextures(1, &result.textureId);

    glBindTexture(GL_TEXTURE_2D, result.textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(                   // create square texture with size power of two
            GL_TEXTURE_2D,
            0,
            GL_RGBA,                // GL_ALPHA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA
            result.textureWidth,    // width
            result.textureHeight,   // height
            0,                      // border must be a zero
            GL_RGBA,                // format GL_ALPHA, GL_RGB, GL_RGBA, GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
            GL_UNSIGNED_BYTE,       // GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, and GL_UNSIGNED_SHORT_5_5_5_1.
            nullptr
            );
    glTexSubImage2D(                // load rectangle image to texture
            GL_TEXTURE_2D,
            0,
            0,                      // xoffset
            0,                      // yoffset
            result.width,
            result.height,
            GL_RGBA,                // GL_ALPHA, GL_RGB, GL_RGBA, GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
            GL_UNSIGNED_BYTE,       // GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, and GL_UNSIGNED_SHORT_5_5_5_1.
            data.data()
            );

    return result;
}
