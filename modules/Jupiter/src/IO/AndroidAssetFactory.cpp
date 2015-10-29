/*
 * AndroidAssetFactory.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: pavel
 */

#include "Jupiter/IO/AndroidAssetFactory.h"

namespace jupiter {

using namespace std;

class AssetBuffer: public Buffer {
public:
    AssetBuffer(AAssetManager *assetManager, const string& fileName) :
        fileName(fileName) {
        unique_ptr<AAsset, function<void(AAsset*)>> f(
            AAssetManager_open(assetManager, fileName.c_str(), AASSET_MODE_BUFFER), [](AAsset* a) {
                AAsset_close(a);
            });
        jassert(f, "can't open file " + fileName);

        auto size = AAsset_getLength(f.get());
        buffer.resize(size);

        char* ptr = reinterpret_cast<char*>(buffer.data());

        auto res = AAsset_read(f.get(), ptr, size);
        jassert(res == size, "can't read file");

        ptr = reinterpret_cast<char*>(buffer.data());
        setg(ptr, ptr, ptr + buffer.capacity());
    }
    virtual ~AssetBuffer() {
        cout << __FUNCTION__ << ": " << fileName << endl;
    }

private:
    string fileName;
};

AndroidAssetFactory::AndroidAssetFactory(AAssetManager *assetManager) :
    _assetManager(assetManager) {
}

AndroidAssetFactory::~AndroidAssetFactory() {
}

unique_ptr<Buffer> AndroidAssetFactory::create(string const& fileName) {
    return make_unique_<AssetBuffer>(_assetManager, fileName);
}

} /* namespace jupiter */

void setAndroidAssetManager(JNIEnv*, jobject assetManager) {
}
