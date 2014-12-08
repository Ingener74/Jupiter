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

class Image
{
public:
    enum class Type
    {
        RGB, RGBA
    };

    Image(const std::string& fileName);
    Image(int width = 0, int height = 0, Type = Type::RGB, std::vector<uint8_t> data = {});
//    Image(Image&&);
//    Image& operator=(Image&&);
    virtual ~Image() = default;

    int width = 0, height = 0;
    Type type =  Type::RGB;
    std::vector<uint8_t> data;

    friend std::ostream& operator<<(std::ostream&, const Image&);
};

}  // namespace ndk_game

#endif /* IMAGE_H_ */
