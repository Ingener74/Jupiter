/*
 * TextureLoader.h
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_

#include <Jupiter/Common.h>
#include <Jupiter/Image.h>

namespace ndk_game
{

class TextureLoader
{
public:
    using Ptr = std::shared_ptr<TextureLoader>;

    TextureLoader();
    virtual ~TextureLoader();

    virtual Image load();
private:
    Image _image;
};

} /* namespace ndk_game */

#endif /* TEXTURELOADER_H_ */
