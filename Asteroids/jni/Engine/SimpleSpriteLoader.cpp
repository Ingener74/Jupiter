/*
 * SimpleSpriteLoader.cpp
 *
 *  Created on: May 29, 2014
 *      Author: pavel
 */

#include <Engine/SimpleSpriteLoader.h>

namespace ndk_game
{

SimpleSpriteLoader::SimpleSpriteLoader(float * vertexes, uint32_t vertexCount,
        SpriteType st) :
        _v(vertexes), _vc(vertexCount), _st(st)
{
}

SimpleSpriteLoader::~SimpleSpriteLoader()
{
}

const float* SimpleSpriteLoader::getVertexes() const throw ()
{
    return _v;
}

uint32_t SimpleSpriteLoader::getVertexCount() const throw ()
{
    return _vc;
}

SimpleSpriteLoader::SpriteType SimpleSpriteLoader::getSpriteType() const throw ()
{
    return _st;
}

} /* namespace ndk_game */

