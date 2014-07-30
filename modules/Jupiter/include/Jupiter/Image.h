/*
 * Image.h
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <Engine/Common.h>

namespace ndk_game
{

struct Image
{
    enum class Type
    {
        RGB, RGBA
    };
    int width, height;
    Type type;
    std::shared_ptr<uint8_t> data;
};

std::ostream& operator<<(std::ostream& sout, const Image& image);

}  // namespace ndk_game

#endif /* IMAGE_H_ */
