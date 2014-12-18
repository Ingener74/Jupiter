/*
 * TextureBuilder.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include <sstream>

#include <boost/spirit/include/qi.hpp>

#include <Jupiter/TextureBuilder.h>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

using namespace std;

shared_ptr<TextureImpl> TextureBuilder::create( const string& texture )
{
    namespace q = boost::spirit::qi;

    vector<string> phrases;

    auto res = q::phrase_parse(
            begin(texture),
            end(texture),
            *q::lexeme[+~q::char_(":")],
            q::char_(":"),
            phrases
    );

    string type = phrases.size() > 1 ? phrases.front() : "file", parameter = phrases.back();

    return phrases.size() < 3 ? factoryRegister()[type]->create(parameter) :
           throw JupiterError("bad texture " +
                   [&](){ stringstream s; for(auto i: phrases) s << i << ", "; return s.str(); }());

    auto factory = factoryRegister()[type];
    if(!factory)
        throw JupiterError("have no factory for type " + type);

    return factory->create(parameter);
}

void TextureBuilder::addFactory(const std::string& type, std::shared_ptr<Factory> factory )
{
    factoryRegister()[ type ] = factory;
}

map<string, shared_ptr<TextureBuilder::Factory> >& TextureBuilder::factoryRegister()
{
    static map<string, shared_ptr<TextureBuilder::Factory> > reg;
    return reg;
}

map<string, shared_ptr<TextureImpl> >& TextureBuilder::textureRegister()
{
    static map<string, shared_ptr<TextureImpl>> textureRegister;
    return textureRegister;
}

} /* namespace jupiter */
