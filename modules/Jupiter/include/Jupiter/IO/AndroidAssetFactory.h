/*
 * AndroidAssetFactory.h
 *
 *  Created on: Oct 29, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_IO_ANDROIDASSETFACTORY_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_IO_ANDROIDASSETFACTORY_H_

#ifdef SWIG

    void setAndroidAssetManager(JNIEnv*, jobject assetManager);

#else
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
#endif

#include "Jupiter/File.h"

namespace jupiter {

void setAndroidAssetManager(JNIEnv*, jobject assetManager);

class AndroidAssetFactory: public BufferFactory {
public:
    AndroidAssetFactory(AAssetManager *assetManager);
    virtual ~AndroidAssetFactory();

    virtual std::unique_ptr<Buffer> create(const std::string& fileName);

private:
    AAssetManager *_assetManager;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_IO_ANDROIDASSETFACTORY_H_ */
