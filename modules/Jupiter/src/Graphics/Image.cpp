/*
 * Image.cpp
 *
 *  Created on: May 27, 2014
 *      Author: ingener
 */

#include <string>
#include <Jupiter/Image.h>

namespace jupiter
{

using namespace std;

ostream& operator <<(ostream& out, const Image& r)
{
    return out << "Image: " << r.width << " x " << r.height << ", " <<
            (r.type == Image::Type::RGB ? string("RGB") : string("RGBA"));
}

}  // namespace jupiter

