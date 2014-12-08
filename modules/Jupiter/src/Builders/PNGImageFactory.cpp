/*
 * PNGImageFactory.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: pavel
 */

#include <Jupiter/JupiterError.h>
#include <Jupiter/detail/PNGImageFactory.h>

namespace jupiter
{

using namespace std;

PNGImageFactory::PNGImageFactory()
{
}

PNGImageFactory::~PNGImageFactory()
{
}

Image PNGImageFactory::create(const std::string& fileName)
{
    file = ResourceManager::createResource(fileName);

    png_byte lHeader[8];
    png_structp lPngPtr = nullptr;
    png_infop lInfoPtr = nullptr;
    png_bytep* lRowPtrs = nullptr;
    png_int_32 lRowSize;
    bool lTransparency;

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

//    png_uint_32 lWidth, lHeight;
    png_uint_32 lWidth, lHeight;

    png_get_IHDR(lPngPtr, lInfoPtr, &lWidth, &lHeight, &lDepth, &lColorType, nullptr, nullptr, nullptr);

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

    Image::Type res_type;

    switch (lColorType)
    {
    case PNG_COLOR_TYPE_PALETTE:
        png_set_palette_to_rgb(lPngPtr);
        res_type = lTransparency ? Image::Type::RGBA : Image::Type::RGB;
        break;
    case PNG_COLOR_TYPE_RGB:
        res_type = lTransparency ? Image::Type::RGBA : Image::Type::RGB;
        break;
    case PNG_COLOR_TYPE_RGBA:
        res_type = Image::Type::RGBA;
        break;
    case PNG_COLOR_TYPE_GRAY:
        png_set_expand_gray_1_2_4_to_8(lPngPtr);
        res_type = Image::Type::RGBA;
        break;
    case PNG_COLOR_TYPE_GA:
        png_set_expand_gray_1_2_4_to_8(lPngPtr);
        res_type = Image::Type::RGBA;
        break;
    }

    png_read_update_info(lPngPtr, lInfoPtr);

    lRowSize = png_get_rowbytes(lPngPtr, lInfoPtr);
    if (lRowSize <= 0) throw std::runtime_error("some error 4");

    auto imageBuffer = unique_ptr<png_byte[]>(new png_byte[lRowSize * lHeight]);

    /**
     * TODO rename errors
     */

    auto imBuf = imageBuffer.get();

    lRowPtrs = new png_bytep[lHeight];
    if (!lRowPtrs) throw std::runtime_error("some error 6");
    for (int32_t i = 0; i < lHeight; ++i)
    {
        lRowPtrs[lHeight - (i + 1)] = imBuf + i * lRowSize;
    }
    png_read_image(lPngPtr, lRowPtrs);

    png_destroy_read_struct(&lPngPtr, &lInfoPtr, NULL);
    delete[] lRowPtrs;

    int w = lWidth;
    int h = lHeight;
    uint8_t* p = imageBuffer.get();
    int s = w * h * (res_type == Image::Type::RGBA ? 4 : 3);

    return {w, h, res_type, {p, p + s}};
}

void PNGImageFactory::pngRwCallback(png_structp pngStruct, png_bytep data, png_size_t size)
{
    auto* self = static_cast<PNGImageFactory*>(png_get_io_ptr(pngStruct));
    self->file->read(reinterpret_cast<char*>(data), size);
}

} /* namespace jupiter */
