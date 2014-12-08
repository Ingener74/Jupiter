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

class SpriteBuilder
{
public:
    friend class Sprite;

    class Factory
    {
    public:
        virtual Sprite create(const std::string& spriteId) = 0;
        virtual ~Factory() = default;

    protected:
        Factory() = default;
    };

    static void pushSpriteFactory(std::shared_ptr<Factory>);
    static void popSpriteFactory();

private:
    static Sprite create(const std::string& spriteId);

    static std::map<std::string, std::shared_ptr<Factory>>& Register();

    SpriteBuilder() = default;
    virtual ~SpriteBuilder() = default;
};

}

#endif /* SPRITEBUILDER_H_ */
