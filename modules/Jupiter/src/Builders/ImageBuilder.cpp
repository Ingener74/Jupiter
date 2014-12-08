/*
 * ImageBuilder.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: pavel
 */

#include <boost/spirit/include/qi.hpp>

#include <Jupiter/detail/ImageBuilder.h>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

using namespace std;

void ImageBuilder::addFactory(const string& extension, shared_ptr<Factory> factory)
{
    if (Register()[extension])
        cerr << "warning: already have factory for that externsion " << extension << endl;
    Register()[extension] = factory;
}

Image ImageBuilder::create(const string& fileName)
{
    auto ext = getFileExtention(fileName);
    auto factory = Register()[ext];

    if(!factory)
        throw JupiterError("have no factories for that file extension " + ext);

    return factory->create(fileName);
}

map<string, shared_ptr<ImageBuilder::Factory> >& ImageBuilder::Register()
{
    static map<string, shared_ptr<ImageBuilder::Factory> > reg;
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
