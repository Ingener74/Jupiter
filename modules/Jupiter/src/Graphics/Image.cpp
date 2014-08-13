/*
 * Image.cpp
 *
 *  Created on: May 27, 2014
 *      Author: ingener
 */

#include <Jupiter/Image.h>

namespace jupiter
{

using namespace std;

ostream& operator <<(ostream& sout, const Image& image)
{
	string type = (image.type == Image::Type::RGB) ? "RGB" : "RGBA";
	sout << "Image: " << image.width << " x " << image.height << ", " << type;
	return sout;
}

}  // namespace jupiter

