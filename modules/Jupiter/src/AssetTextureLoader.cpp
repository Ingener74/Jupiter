/*
 * AssetTextureLoader.cpp
 *
 *  Created on: May 26, 2014
 *      Author: pavel
 */

#include <Jupiter/AssetTextureLoader.h>

namespace jupiter
{

using namespace std;

AssetTextureLoader::AssetTextureLoader(android_app* application,
        const std::string& path) :
        _app(application), _path(path)
{
}

AssetTextureLoader::~AssetTextureLoader()
{
}

Image AssetTextureLoader::load()
{
    cout << "Loading texture " << _path << endl;

    Image result;

    png_byte lHeader[8];
    png_structp lPngPtr = NULL;
    png_infop lInfoPtr = NULL;
    png_byte* lImageBuffer = NULL;
    png_bytep* lRowPtrs = NULL;
    png_int_32 lRowSize;
    bool lTransparency;

    asset = std::shared_ptr<AAsset>(
            AAssetManager_open(
                    _app->activity->assetManager,
                    _path.c_str(),
                    AASSET_MODE_UNKNOWN),
                    [](AAsset* file)
    {
        AAsset_close(file);
    });

    if(!asset)throw std::runtime_error(_path + "can't open asset");

    int res = AAsset_read(asset.get(), lHeader, sizeof(lHeader));
    if (res < 0) throw std::runtime_error("can't read png header from asset");

    if (png_sig_cmp(lHeader, 0, 8) != 0) throw std::runtime_error(
            "can't signature mismatch");

    lPngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
    NULL, NULL, NULL);
    if (!lPngPtr) throw std::runtime_error("some error 1");
    lInfoPtr = png_create_info_struct(lPngPtr);
    if (!lInfoPtr) throw std::runtime_error("some error 2");

    png_set_read_fn(lPngPtr, this, pngRwCallback);
    if (setjmp(png_jmpbuf(lPngPtr))) throw std::runtime_error(
            "can't set read callback");

    png_set_sig_bytes(lPngPtr, 8);
    png_read_info(lPngPtr, lInfoPtr);
    png_int_32 lDepth, lColorType;
    png_uint_32 lWidth, lHeight;
    png_get_IHDR(lPngPtr, lInfoPtr, &lWidth, &lHeight,
            static_cast<int*>(&lDepth), static_cast<int*>(&lColorType),
            NULL, NULL, NULL);
    result.width = lWidth;
    result.height = lHeight;

    lTransparency = false;
    if (png_get_valid(lPngPtr, lInfoPtr, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(lPngPtr);
        lTransparency = true;
        throw std::runtime_error("some error 3");
    }
    if (lDepth < 8)
    {
        png_set_packing(lPngPtr);
    }
    else if (lDepth == 16)
    {
        png_set_strip_16(lPngPtr);
    }

    switch (lColorType)
    {
        case PNG_COLOR_TYPE_PALETTE:
            png_set_palette_to_rgb(lPngPtr);
            result.type = lTransparency ? Image::Type::RGBA : Image::Type::RGB;
            break;
        case PNG_COLOR_TYPE_RGB:
            result.type = lTransparency ? Image::Type::RGBA : Image::Type::RGB;
            break;
        case PNG_COLOR_TYPE_RGBA:
            result.type = Image::Type::RGBA;
            break;
        case PNG_COLOR_TYPE_GRAY:
            png_set_expand_gray_1_2_4_to_8(lPngPtr);
            result.type = Image::Type::RGBA;
            break;
        case PNG_COLOR_TYPE_GA:
            png_set_expand_gray_1_2_4_to_8(lPngPtr);
            result.type = Image::Type::RGBA;
            break;
    }

    png_read_update_info(lPngPtr, lInfoPtr);

    lRowSize = png_get_rowbytes(lPngPtr, lInfoPtr);
    if (lRowSize <= 0) throw std::runtime_error("some error 4");
    lImageBuffer = new png_byte[lRowSize * lHeight];
    if (!lImageBuffer) throw std::runtime_error("some error 5");

    /**
     * TODO rename errors
     */

    lRowPtrs = new png_bytep[lHeight];
    if (!lRowPtrs) throw std::runtime_error("some error 6");
    for (int32_t i = 0; i < lHeight; ++i)
    {
        lRowPtrs[lHeight - (i + 1)] = lImageBuffer + i * lRowSize;
    }
    png_read_image(lPngPtr, lRowPtrs);

    png_destroy_read_struct(&lPngPtr, &lInfoPtr, NULL);
    delete[] lRowPtrs;

    int size = result.height * result.width *
            ((result.type == Image::Type::RGBA) ? 4 : 3);

    result.data = std::shared_ptr<uint8_t>(new uint8_t[size], [](uint8_t * data)
    {
        delete[] data;
    });

    memcpy(result.data.get(), lImageBuffer, size);

    delete[] lImageBuffer;

    return result;
}

void AssetTextureLoader::pngRwCallback(png_structp pngStruct, png_bytep data,
        png_size_t size)
{
    AssetTextureLoader* self = static_cast<AssetTextureLoader*>(png_get_io_ptr(
            pngStruct));

    AAsset_read(self->asset.get(), data, size);
}

} /* namespace ndk_game */

