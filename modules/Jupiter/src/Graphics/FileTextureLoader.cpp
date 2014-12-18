/*
 * FileTextureLoader.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: pavel
 */

#include <iostream>
#include <vector>
#include <memory>

#include <png.h>

#include <Jupiter/FileTextureLoader.h>
#include <Jupiter/JupiterError.h>
#include <Jupiter/ResourceManager.h>

namespace jupiter
{

using namespace std;

FileTextureLoader::FileTextureLoader(const std::string& fileName) :
        fileName(fileName)
{
}

FileTextureLoader::~FileTextureLoader()
{
}

Image FileTextureLoader::load()
{
    ImageImpl result;

    png_byte lHeader[8];
    png_structp lPngPtr = nullptr;
    png_infop lInfoPtr = nullptr;
    png_byte* lImageBuffer = nullptr;
    png_bytep* lRowPtrs = nullptr;
    png_int_32 lRowSize;
    bool lTransparency;

    file = ResourceManager::createResource(fileName);

    file->read(reinterpret_cast<char*>(lHeader), sizeof(lHeader));

    if (png_sig_cmp(lHeader, 0, 8) != 0) throw std::runtime_error("can't signature mismatch");

    lPngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!lPngPtr) throw JupiterError("some error 1");

    lInfoPtr = png_create_info_struct(lPngPtr);
    if (!lInfoPtr) throw JupiterError("some error 2");

    png_set_read_fn(lPngPtr, this, pngRwCallback);
    if (setjmp(png_jmpbuf(lPngPtr))) throw JupiterError("can't set read callback");

    png_set_sig_bytes(lPngPtr, 8);
    png_read_info(lPngPtr, lInfoPtr);

    int lDepth = 0, lColorType = 0;

//    png_int_32 /*lDepth, lColorType*/;

    png_uint_32 lWidth, lHeight;

    png_get_IHDR(lPngPtr, lInfoPtr, &lWidth, &lHeight, &lDepth, &lColorType, nullptr, nullptr, nullptr);
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

    int size = result.height * result.width * ((result.type == Image::Type::RGBA) ? 4 : 3);

    result.data = {
        static_cast<uint8_t*>(lImageBuffer),
        static_cast<uint8_t*>(lImageBuffer + size)
    };

    delete[] lImageBuffer;

    return result;

}

void FileTextureLoader::pngRwCallback(png_structp pngStruct, png_bytep data, png_size_t size)
{
    auto* self = static_cast<FileTextureLoader*>(png_get_io_ptr(pngStruct));
    self->file->read(reinterpret_cast<char*>(data), size);
}

} /* namespace jupiter */
