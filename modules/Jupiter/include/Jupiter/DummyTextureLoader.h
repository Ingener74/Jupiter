/*
 * DummyTextureLoader.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef DUMMYTEXTURELOADER_H_
#define DUMMYTEXTURELOADER_H_

#include <Jupiter/TextureLoader.h>

namespace jupiter
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
