/*
 * DummyTextureLoader.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef DUMMYTEXTURELOADER_H_
#define DUMMYTEXTURELOADER_H_

#include <Engine/TextureLoader.h>

namespace ndk_game
{

class DummyTextureLoader: public TextureLoader
{
public:
    DummyTextureLoader();
    virtual ~DummyTextureLoader();

    virtual Image load();
};

} /* namespace ndk_game */

#endif /* DUMMYTEXTURELOADER_H_ */
