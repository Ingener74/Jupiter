/*
 * AssetTextureLoader.h
 *
 *  Created on: May 26, 2014
 *      Author: pavel
 */

#ifndef ASSETTEXTURELOADER_H_
#define ASSETTEXTURELOADER_H_

#include <Engine/TextureLoader.h>

namespace ndk_game
{

class AssetTextureLoader: public TextureLoader
{
public:
    AssetTextureLoader();
    virtual ~AssetTextureLoader();

    virtual Image load();
};

} /* namespace ndk_game */

#endif /* ASSETTEXTURELOADER_H_ */
