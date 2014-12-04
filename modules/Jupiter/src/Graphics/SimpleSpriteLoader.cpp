/*
 * SimpleSpriteLoader.cpp
 *
 *  Created on: May 29, 2014
 *      Author: pavel
 */

#include <Jupiter/SimpleSpriteLoader.h>

namespace jupiter
{

SimpleSpriteLoader::SimpleSpriteLoader(float * vertexes, uint32_t vertexCount, SpriteType st) :
        _v(vertexes), _vc(vertexCount), _st(st)
{
}

SimpleSpriteLoader::~SimpleSpriteLoader()
{
}

const float* SimpleSpriteLoader::getVertexes() const
{
    return _v;
}

uint32_t SimpleSpriteLoader::getVertexCount() const
{
    return _vc;
}

SimpleSpriteLoader::SpriteType SimpleSpriteLoader::getSpriteType() const
{
    return _st;
}

} /* namespace ndk_game */

