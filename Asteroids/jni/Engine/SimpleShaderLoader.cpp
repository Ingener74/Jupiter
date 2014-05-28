/*
 * SimpleShaderLoader.cpp
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#include <Engine/SimpleShaderLoader.h>

namespace ndk_game
{

SimpleShaderLoader::SimpleShaderLoader(const std::string& vertexShader,
        const std::string fragmentShader) :
        _vs(vertexShader), _fs(fragmentShader)
{
}

SimpleShaderLoader::~SimpleShaderLoader()
{
}

const char* SimpleShaderLoader::getVertexShader() const
{
    return _vs.c_str();
}

const char* SimpleShaderLoader::getFragmentShader() const
{
    return _fs.c_str();
}

} /* namespace ndk_game */
