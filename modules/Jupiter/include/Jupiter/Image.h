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
#include <memory>

namespace jupiter
{

class ImageImpl;

class Image
{
public:
    enum class Type
    {
        RGB, RGBA
    };

    Image(const std::string& fileName);

    Image() = default;
    virtual ~Image() = default;

    int getWidth() const;
    int getHeight() const;
    const uint8_t* getData() const;
    Type getType() const;

    friend std::ostream& operator<<(std::ostream&, const Image&);

private:
    std::shared_ptr<ImageImpl> _impl;
};

}  // namespace ndk_game

#endif /* IMAGE_H_ */
