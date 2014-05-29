/*
 * SimpleSpriteLoader.h
 *
 *  Created on: May 29, 2014
 *      Author: pavel
 */

#ifndef SIMPLESPRITELOADER_H_
#define SIMPLESPRITELOADER_H_

#include <Engine/ISpriteLoader.h>

namespace ndk_game
{

class SimpleSpriteLoader: public ISpriteLoader
{
public:
    SimpleSpriteLoader(float * vertexes, uint32_t vertexCount);
    virtual ~SimpleSpriteLoader();

    virtual float * getVertexes() const throw ();
    virtual uint32_t getVertexCount() const throw ();

private:
    float * _v;
    uint32_t _vc;
};

} /* namespace ndk_game */

#endif /* SIMPLESPRITELOADER_H_ */
