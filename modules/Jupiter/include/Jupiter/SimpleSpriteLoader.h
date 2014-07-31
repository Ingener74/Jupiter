/*
 * SimpleSpriteLoader.h
 *
 *  Created on: May 29, 2014
 *      Author: pavel
 */

#ifndef SIMPLESPRITELOADER_H_
#define SIMPLESPRITELOADER_H_

#include <Jupiter/ISpriteLoader.h>

namespace ndk_game
{

class SimpleSpriteLoader: public ISpriteLoader
{
public:
    SimpleSpriteLoader(float * vertexes, uint32_t vertexCount, SpriteType spriteType = SpriteType::Triangles);
    virtual ~SimpleSpriteLoader();

    virtual const float * getVertexes() const throw ();
    virtual uint32_t getVertexCount() const throw ();
    virtual SpriteType getSpriteType() const throw ();

private:
    float * _v;
    uint32_t _vc;
    SpriteType _st;
};

} /* namespace ndk_game */

#endif /* SIMPLESPRITELOADER_H_ */
