/*
 * SpriteBuilder.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: pavel
 */

//#include <boost/spirit/include/qi.hpp>
#include "SpriteBuilder.h"

namespace jupiter
{

namespace detail
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

    return Register()["sprite id"]->create(spriteId);
}

void SpriteBuilder::pushSpriteFactory(std::shared_ptr<Factory>)
{
}

void SpriteBuilder::popSpriteFactory()
{
}

map<string, shared_ptr<SpriteBuilder::Factory>>& SpriteBuilder::Register()
{
    static map<string, shared_ptr<SpriteBuilder::Factory>> reg;
    return reg;
}

}  // namespace detail

} /* namespace jupiter */

