/*
 * DummyTextureLoader.cpp
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#include <Engine/DummyTextureLoader.h>

namespace ndk_game
{

DummyTextureLoader::DummyTextureLoader()
{
}

DummyTextureLoader::~DummyTextureLoader()
{
}

Image DummyTextureLoader::load()
{
    Image result;
    result.width = 512;
    result.height = 512;
    result.type = Image::Type::RGBA;

    result.data = std::shared_ptr<uint8_t>(
            new uint8_t[result.width * result.height * 4], [](uint8_t* p)
            {
                delete [] p;
            });

    uint8_t * p = result.data.get();
    for (int i = 0; i < result.height; ++i) {
        for (int j = 0; j < result.width; ++j) {
            *p++ = 35;
            *p++ = 124;
            *p++ = 0;
            *p++ = 255;
        }
    }

    return result;
}

} /* namespace ndk_game */
