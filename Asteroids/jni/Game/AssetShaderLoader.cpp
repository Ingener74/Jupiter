/*
 * AssetShaderLoader.cpp
 *
 *  Created on: May 31, 2014
 *      Author: ingener
 */

#include <Game/AssetShaderLoader.h>

using namespace ndk_game;

AssetShaderLoader::AssetShaderLoader(AAssetManager* aMgr, const std::string& vf,
        const std::string& ff)
{
    Log() << "Loading shader " << vf;

    AAsset *vertexAsset = AAssetManager_open(aMgr, vf.c_str(), AASSET_MODE_UNKNOWN);
    if (!vertexAsset) throw std::runtime_error("can't open vertex shader asset file");

    int vertexShaderLen = AAsset_getLength(vertexAsset);
    std::unique_ptr<char[]> vertexShaderBuf(new char[vertexShaderLen + 1]);
    memset(vertexShaderBuf.get(), 0, vertexShaderLen + 1);
    AAsset_read(vertexAsset, vertexShaderBuf.get(), vertexShaderLen);

    _vs = std::string(vertexShaderBuf.get());

    AAsset_close(vertexAsset);

    Log() << "Loading shader " << ff;

    AAsset *fragmentShaderAsset = AAssetManager_open(aMgr, ff.c_str(), AASSET_MODE_UNKNOWN);
    if(!fragmentShaderAsset)throw std::runtime_error("can't open fragment shader asset file");

    int fragmentShaderLen = AAsset_getLength(fragmentShaderAsset);
    std::unique_ptr<char[]> fragmentShaderBuf(new char[fragmentShaderLen + 1]);
    memset(fragmentShaderBuf.get(), 0, fragmentShaderLen + 1);
    AAsset_read(fragmentShaderAsset, fragmentShaderBuf.get(), fragmentShaderLen);

    _fs = std::string(fragmentShaderBuf.get());

    AAsset_close(fragmentShaderAsset);
}

AssetShaderLoader::~AssetShaderLoader()
{
    Log() << "AssetShaderLoader::~AssetShaderLoader()";
}

const char* AssetShaderLoader::getVertexShader() const
{
    return _vs.c_str();
}

const char* AssetShaderLoader::getFragmentShader() const
{
    return _fs.c_str();
}
