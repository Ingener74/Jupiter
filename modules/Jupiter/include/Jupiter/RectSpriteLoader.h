/*
 * RectSpriteLoader.h
 *
 *  Created on: May 30, 2014
 *      Author: pavel
 */

#ifndef RECTSPRITELOADER_H_
#define RECTSPRITELOADER_H_

#include <array>
#include <cstdint>

#include <Jupiter/ISpriteLoader.h>
#include <Jupiter/Rect.h>

namespace jupiter
{

class RectSpriteLoader: public ISpriteLoader
{
public:
    RectSpriteLoader(float w, float h, float z, float tx1, float tx2, float ty1, float ty2);
    RectSpriteLoader(Rect rect, float z, float tx1, float tx2, float ty1, float ty2);
    virtual ~RectSpriteLoader() = default;

    virtual const float * getVertexes() const;
    virtual uint32_t getVertexCount() const;
    virtual SpriteType getSpriteType() const;

private:
    std::array<float, 6 * 5> _data;
    ISpriteLoader::SpriteType _type;
};

} /* namespace ndk_game */

#endif /* RECTSPRITELOADER_H_ */
