/*
 * Image.h
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include <iostream>
#include <vector>

namespace jupiter
{

struct Image
{
    enum class Type
    {
        RGB, RGBA
    };
    int width, height;
    Type type;
//    std::shared_ptr<uint8_t> data;
    std::vector<uint8_t> data;

    friend std::ostream& operator<<(std::ostream&, const Image&);
};


}  // namespace ndk_game

#endif /* IMAGE_H_ */
