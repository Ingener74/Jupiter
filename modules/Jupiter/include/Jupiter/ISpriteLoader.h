/*
 * ISpriteLoader.h
 *
 *  Created on: May 29, 2014
 *      Author: pavel
 */

#ifndef ISPRITELOADER_H_
#define ISPRITELOADER_H_

#include <cstdint>

namespace jupiter
{

class ISpriteLoader
{
public:
    virtual ~ISpriteLoader() = default;

    enum class SpriteType
    {
        Triangles, TriangleFan, TriangleStrip, LineStrip
    };

    virtual const float * getVertexes() const = 0;
    virtual uint32_t getVertexCount() const = 0;
    virtual SpriteType getSpriteType() const = 0;

protected:
    ISpriteLoader() = default;
};

} /* namespace ndk_game */

#endif /* ISPRITELOADER_H_ */
