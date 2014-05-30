/*
 * RectSpriteLoader.h
 *
 *  Created on: May 30, 2014
 *      Author: pavel
 */

#ifndef RECTSPRITELOADER_H_
#define RECTSPRITELOADER_H_

#include <Engine/ISpriteLoader.h>

namespace ndk_game
{

class RectSpriteLoader: public ISpriteLoader
{
public:
    RectSpriteLoader(float w, float h, float z, float tx1, float tx2, float ty1,
            float ty2);
    virtual ~RectSpriteLoader();

    virtual const float * getVertexes() const throw ();
    virtual uint32_t getVertexCount() const throw ();
    virtual SpriteType getSpriteType() const throw ();

private:
    float _data[6 * 5];
};

} /* namespace ndk_game */

#endif /* RECTSPRITELOADER_H_ */
