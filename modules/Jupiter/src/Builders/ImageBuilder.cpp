/*
 * ImageBuilder.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: pavel
 */

#include <Jupiter/detail/ImageBuilder.h>

namespace jupiter
{

using namespace std;

void ImageBuilder::addFactory(const string& extension, shared_ptr<Factory> factory)
{
    Register()[extension] = factory;
}

Image ImageBuilder::create(const string& fileName)
{
    return Register()[getFileExtention(fileName)]->create(fileName);
}

map<string, shared_ptr<ImageBuilder::Factory> >& ImageBuilder::Register()
{
    static map<string, shared_ptr<ImageBuilder::Factory> > reg;
    return reg;
}

string ImageBuilder::getFileExtention(const string& fileName)
{
}

} /* namespace jupiter */
