/*
 * ImageBuilder.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: pavel
 */

#include <boost/spirit/include/qi.hpp>

#include <Jupiter/ImageBuilder.h>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

using namespace std;

void ImageBuilder::addFactory(const string& extension, shared_ptr<Factory> factory)
{
    if (factoryRegister()[extension])
        cerr << "warning: already have factory for that externsion " << extension << endl;
    factoryRegister()[extension] = factory;
}

shared_ptr<ImageImpl> ImageBuilder::create(const string& fileName)
{
    auto imageImpl = imageRegister()[fileName];
    if(imageImpl)
        return imageImpl;

    auto ext = getFileExtention(fileName);
    auto factory = factoryRegister()[ext];

    if(!factory)
        throw JupiterError("have no factories for that file extension " + ext);

    auto imImpl = factory->create(fileName);
    imageRegister()[fileName] = imImpl;

    return imImpl;
}

map<string, shared_ptr<ImageBuilder::Factory> >& ImageBuilder::factoryRegister()
{
    static map<string, shared_ptr<ImageBuilder::Factory> > reg;
    return reg;
}

map<string, shared_ptr<ImageImpl> >& ImageBuilder::imageRegister()
{
    static map<string, shared_ptr<ImageImpl> > reg;
    return reg;
}

string ImageBuilder::getFileExtention(const string& fileName)
{
    namespace q = boost::spirit::qi;

    vector<string> parts;

    auto res = q::phrase_parse(
            begin(fileName),
            end(fileName),
            *q::lexeme[+~q::char_(".")],
            q::char_("."),
            parts
    );

    return parts.back();
}

} /* namespace jupiter */
