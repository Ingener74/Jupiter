/*
 * Image.cpp
 *
 *  Created on: May 27, 2014
 *      Author: ingener
 */

#include <string>
#include <Jupiter/Image.h>

#include <Jupiter/detail/ImageBuilder.h>

namespace jupiter
{

using namespace std;

Image::Image(const std::string& fileName) :
        Image(ImageBuilder::create(fileName))
{
}

Image::Image(int width, int height, Type type, std::vector<uint8_t> data) :
        width(width), height(height), type(type), data(data)
{
}

//Image::Image(Image&& rr)
//{
//    *this = rr;
//}
//
//Image& Image::operator =(Image&& rr)
//{
//    width = move(rr.width);
//    height = move(rr.height);
//    type = move(rr.type);
//    data = move(rr.data);
//    return *this;
//}

ostream& operator <<(ostream& out, const Image& r)
{
    return out << "Image: " << r.width << " x " << r.height << ", "
            << (r.type == Image::Type::RGB ? string("RGB") : string("RGBA"));
}

}  // namespace jupiter

