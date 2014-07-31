/*
 * ISpriteLoader.h
 *
 *  Created on: May 29, 2014
 *      Author: pavel
 */

#ifndef ISPRITELOADER_H_
#define ISPRITELOADER_H_

#include <Jupiter/Common.h>

namespace ndk_game
{

class ISpriteLoader
{
public:
    using Ptr = std::shared_ptr<ISpriteLoader>;

    virtual ~ISpriteLoader()
    {
    }

    enum class SpriteType
    {
        Triangles, TriangleFan, TriangleStrip, LineStrip
    };

    virtual const float * getVertexes() const throw () = 0;
    virtual uint32_t getVertexCount() const throw () = 0;
    virtual SpriteType getSpriteType() const throw () = 0;

protected:
    ISpriteLoader()
    {
    }
};

} /* namespace ndk_game */

#endif /* ISPRITELOADER_H_ */
