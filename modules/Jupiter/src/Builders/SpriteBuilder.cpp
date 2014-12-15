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

    namespace q = boost::spirit::qi;

    vector<string> phrases;

    auto res = q::phrase_parse(
            begin(spriteId),
            end(spriteId),
            *q::lexeme[+~q::char_(":")],
            q::char_(":"),
            phrases
    );


    cout << "res " << res << endl;

    for(auto i: phrases)
        cout << "  " << i << endl;

    if(phrases.empty() || phrases.size() > 2)
        throw JupiterError("bad sprite id " + spriteId + " must contain only one double point " +
                           [&](){ stringstream s; for(auto i: phrases) s << i << ", "; return s.str(); }());

    string type = phrases.size() > 1 ? "file" : phrases.front(), parameter = phrases.back();

    return factoryRegister()[type]->create(parameter);
}

void SpriteBuilder::addFactory(const string& spriteType, shared_ptr<Factory> factory)
{
    if(factoryRegister()[spriteType])
        cerr << "warning: already have factory for that type " << spriteType << endl;

    factoryRegister()[spriteType] = factory;
}

map<string, shared_ptr<SpriteBuilder::Factory>>& SpriteBuilder::factoryRegister()
{
    static map<string, shared_ptr<Factory>> reg;
    return reg;
}

} /* namespace jupiter */

