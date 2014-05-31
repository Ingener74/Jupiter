/*
 * AssetShaderLoader.h
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#ifndef ASSETSHADERLOADER_H_
#define ASSETSHADERLOADER_H_

#include <android/asset_manager.h>
#include <Engine/Engine.h>

class AssetShaderLoader: public ndk_game::IShaderLoader
{
public:
    AssetShaderLoader(AAssetManager* assetMgr, const std::string& vertexFile,
            const std::string& fragmentFile);
    virtual ~AssetShaderLoader();

    virtual const char* getVertexShader() const;
    virtual const char* getFragmentShader() const;

private:
    std::string _vs, _fs;
};

#endif /* ASSETSHADERLOADER_H_ */
