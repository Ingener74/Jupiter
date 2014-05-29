/*
 * SimpleSpriteLoader.cpp
 *
 *  Created on: May 29, 2014
 *      Author: pavel
 */

#include <Engine/SimpleSpriteLoader.h>

namespace ndk_game
{

SimpleSpriteLoader::SimpleSpriteLoader(float * vertexes, uint32_t vertexCount) :
        _v(vertexes), _vc(vertexCount)
{
}

SimpleSpriteLoader::~SimpleSpriteLoader()
{
}

float* SimpleSpriteLoader::getVertexes() const throw ()
{
    return _v;
}

uint32_t SimpleSpriteLoader::getVertexCount() const throw ()
{
    return _vc;
}

} /* namespace ndk_game */
