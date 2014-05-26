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
    AssetTextureLoader(android_app* application, const std::string& path);
    virtual ~AssetTextureLoader();

    virtual Image load();
private:
    android_app* _app;
    std::string _path;
};

} /* namespace ndk_game */

#endif /* ASSETTEXTURELOADER_H_ */
