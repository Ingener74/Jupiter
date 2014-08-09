/*
 * SimpleShaderLoader.cpp
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#include <Jupiter/SimpleShaderLoader.h>

namespace jupiter
{

using namespace std;

SimpleShaderLoader::SimpleShaderLoader(const string& vertexShader,
        const string fragmentShader) :
        _vs(vertexShader), _fs(fragmentShader)
{
}

SimpleShaderLoader::~SimpleShaderLoader()
{
}

string SimpleShaderLoader::getVertexShader() const
{
    return _vs.c_str();
}

string SimpleShaderLoader::getFragmentShader() const
{
    return _fs.c_str();
}

} /* namespace ndk_game */
