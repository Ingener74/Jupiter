/*
 * ImageImpl.h
 *
 *  Created on: Dec 15, 2014
 *      Author: pavel
 */

#ifndef IMAGEIMPL_H_
#define IMAGEIMPL_H_

#include <vector>
#include <cstdint>

#include <Jupiter/Image.h>

namespace jupiter
{

class ImageImpl
{
public:
    friend class Image;

    ImageImpl(int width, int height, Image::Type type, std::vector<uint8_t> data);

    friend std::ostream& operator<<(std::ostream&, const ImageImpl&);

private:
    int width = 0, height = 0;
    Image::Type type =  Image::Type::RGB;
    std::vector<uint8_t> data;
};

} /* namespace jupiter */

#endif /* IMAGEIMPL_H_ */
