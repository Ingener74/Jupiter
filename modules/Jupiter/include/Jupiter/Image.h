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

#include "Jupiter/Aware.h"

namespace jupiter {

class Image: public Object{
public:
    enum class Type {
        RGB, RGBA
    };

    Image(const std::string& name);
    virtual ~Image() = default;

    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual const uint8_t* getData() const;
    virtual Type getType() const;

    friend std::ostream& operator<<(std::ostream&, const Image&);

protected:
    int width = 0, height = 0;
    Image::Type type = Image::Type::RGB;
    std::vector<uint8_t> data;
};

}  // namespace ndk_game

#endif /* IMAGE_H_ */
