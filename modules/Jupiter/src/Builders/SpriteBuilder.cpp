/*
 * SpriteBuilder.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: pavel
 */

#include <boost/spirit/include/qi.hpp>

#include <Jupiter/detail/SpriteBuilder.h>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

using namespace std;

Sprite SpriteBuilder::create(const std::string& spriteId)
{
    /*
     * process sprite Id
     *
     * format
     * file:{/concrete/file1.png, /concrete/file2.png} - default
     * camera:{0, 1, 2, ...}
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

    return phrases.size() == 1 ? Register()["file"]->create(spriteId) :
           phrases.size() == 2 ? Register()[phrases[1]]->create(spriteId) :
           throw JupiterError("bad sprite id " + spriteId + " must contain only one double point");
}

void SpriteBuilder::pushSpriteFactory(std::shared_ptr<Factory>)
{
}

void SpriteBuilder::popSpriteFactory()
{
}

map<string, shared_ptr<SpriteBuilder::Factory>>& SpriteBuilder::Register()
{
    static map<string, shared_ptr<Factory>> reg;
    return reg;
}

} /* namespace jupiter */

