/*
 * SpriteBuilder.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: pavel
 */

#include <sstream>

#include <boost/spirit/include/qi.hpp>

#include <Jupiter/detail/SpriteBuilder.h>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

using namespace std;

std::shared_ptr<SpriteImpl> SpriteBuilder::create(const string& spriteId)
{
    /*
     * process sprite Id
     *
     * format
     * file:{/concrete/file1.png, /concrete/file2.png} - default
     * camera:{0, 1, 2, ...}
     * json:{name}
     * ...
     *
     */

    auto sprtImpl = spriteRegister()[spriteId];
    if(sprtImpl)
        return sprtImpl;

    namespace q = boost::spirit::qi;

    vector<string> phrases;

    auto res = q::phrase_parse(
            begin(spriteId),
            end(spriteId),
            *q::lexeme[+~q::char_(":")],
            q::char_(":"),
            phrases
    );

    if(phrases.empty() || phrases.size() > 2)
        throw JupiterError("bad sprite id " + spriteId + " must contain only one double point " +
                           [&](){ stringstream s; for(auto i: phrases) s << i << ", "; return s.str(); }());

    string type = phrases.size() > 1 ? phrases.front() : "file", parameter = phrases.back();

    auto factory = factoryRegister()[type];
    if(!factory)
        throw JupiterError("has no factory for sprite type " + type);

    auto spriteImpl = factory->create(parameter);

    spriteRegister()[spriteId] = spriteImpl;

    return spriteImpl;
}

void SpriteBuilder::addFactory(const string& spriteType, shared_ptr<Factory> factory)
{
    if(factoryRegister()[spriteType])
        cerr << "warning: already have factory for that type " << spriteType << endl;

    factoryRegister()[spriteType] = factory;
}

SpriteBuilder::FactoriesMap& SpriteBuilder::factoryRegister()
{
    static FactoriesMap reg;
    return reg;
}

SpriteBuilder::SpritesMap& SpriteBuilder::spriteRegister()
{
    static SpritesMap reg;
    return reg;
}

} /* namespace jupiter */

