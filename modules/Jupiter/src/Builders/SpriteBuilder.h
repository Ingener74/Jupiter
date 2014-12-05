/*
 * SpriteBuilder.h
 *
 *  Created on: Dec 5, 2014
 *      Author: pavel
 */

#ifndef SPRITEBUILDER_H_
#define SPRITEBUILDER_H_

#include <string>
#include <map>

#include <Jupiter/Sprite.h>

namespace jupiter
{

namespace detail
{

using namespace std;

class SpriteBuilder
{
public:
    class Factory
    {
    public:
        virtual Sprite create(const std::string& spriteId) = 0;
        virtual ~Factory() = default;

    protected:
        Factory() = default;
    };

    static Sprite create(const std::string& spriteId);

    static void pushSpriteFactory(std::shared_ptr<Factory>);
    static void popSpriteFactory();

private:
    static map<string, shared_ptr<Factory>>& Register();

    SpriteBuilder() = default;
    virtual ~SpriteBuilder() = default;
};

}
}

#endif /* SPRITEBUILDER_H_ */
