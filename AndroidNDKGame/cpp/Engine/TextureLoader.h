/*
 * TextureLoader.h
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_

#include <Engine/Common.h>

namespace ndk_game
{

class TextureLoader
{
public:
    TextureLoader();
    virtual ~TextureLoader();

    Image load(){
    }
};

} /* namespace ndk_game */

#endif /* TEXTURELOADER_H_ */
