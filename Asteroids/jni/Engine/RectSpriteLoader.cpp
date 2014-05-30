/*
 * RectSpriteLoader.cpp
 *
 *  Created on: May 30, 2014
 *      Author: pavel
 */

#include <Engine/RectSpriteLoader.h>

namespace ndk_game
{

RectSpriteLoader::RectSpriteLoader(float w, float h, float z, float tx1,
        float tx2, float ty1, float ty2)
{
    /*
     * 1                        2
     * -s s                      s s
     * tx1 ty1                   tx2 ty1
     *
     *
     *
     *
     *
     *
     * 3                        4
     * -s -s                      s -s
     * tx1 ty2                    tx2 ty2
     */

    float data[] =
    {
            // 1 2 3
            -w / 2, h / 2, z, tx1, ty1,
            -w / 2, -h / 2, z, tx1, ty2,
            w / 2, h / 2, z, tx2, ty1,

            // 4 3 2
            w / 2, -h / 2, z, tx2, ty2,
            w / 2, h / 2, z, tx2, ty1,
            -w / 2, -h / 2, z, tx1, ty2, };
    memcpy(_data, data, 6 * 5 * sizeof(float));
}

RectSpriteLoader::~RectSpriteLoader()
{
}

const float* RectSpriteLoader::getVertexes() const throw ()
{
    return _data;
}

uint32_t RectSpriteLoader::getVertexCount() const throw ()
{
    return 6;
}

ISpriteLoader::SpriteType RectSpriteLoader::getSpriteType() const throw ()
{
    return ISpriteLoader::SpriteType::Triangles;
}

} /* namespace ndk_game */
