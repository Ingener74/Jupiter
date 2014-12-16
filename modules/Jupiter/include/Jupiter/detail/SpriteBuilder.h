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

#include <Jupiter/facade/Sprite.h>

namespace jupiter
{

class SpriteBuilder
{
public:
    friend class Sprite;

    class Factory
    {
    public:
        virtual std::shared_ptr<SpriteImpl> create(const std::string& spriteId) = 0;
    };

    static void addFactory(const std::string& spriteType, std::shared_ptr<Factory>);

private:
    static std::shared_ptr<SpriteImpl> create(const std::string& spriteId);

    using FactoriesMap = std::map<std::string, std::shared_ptr<Factory>>;
    using SpritesMap = std::map<std::string, std::shared_ptr<SpriteImpl>>;

    static FactoriesMap& factoryRegister();
    static SpritesMap&   spriteRegister();

    SpriteBuilder() = default;
    virtual ~SpriteBuilder() = default;
};

}

#endif /* SPRITEBUILDER_H_ */
