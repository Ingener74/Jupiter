/*
 * AssetTextureLoader.h
 *
 *  Created on: May 26, 2014
 *      Author: pavel
 */

#ifndef ASSETTEXTURELOADER_H_
#define ASSETTEXTURELOADER_H_

#include <Jupiter/Common.h>
#include <Jupiter/TextureLoader.h>

namespace jupiter
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

    std::shared_ptr<AAsset> asset;

    static void pngRwCallback(png_structp, png_bytep, png_size_t);
};

} /* namespace ndk_game */

#endif /* ASSETTEXTURELOADER_H_ */
