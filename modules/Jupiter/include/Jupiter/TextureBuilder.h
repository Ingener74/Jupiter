/*
 * TextureBuilder.h
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_SRC_BUILDERS_TEXTUREBUILDER_H_
#define MODULES_JUPITER_SRC_BUILDERS_TEXTUREBUILDER_H_

#include <map>
#include <string>
#include <memory>
#include <cstdint>

namespace jupiter
{

class TextureImpl;

class TextureBuilder
{
public:
    class Factory
    {
    public:
        virtual std::shared_ptr<TextureImpl> create( const std::string& texture ) = 0;

        static ulong upperPowerOfTwo(ulong);
    };

    static std::shared_ptr<TextureImpl> create( const std::string& texture );

    static void addFactory(const std::string& type, std::shared_ptr<Factory>);

private:
    TextureBuilder() = delete;
    virtual ~TextureBuilder() = delete;

    static std::map<std::string, std::shared_ptr<Factory>>& factoryRegister();
    static std::map<std::string, std::shared_ptr<TextureImpl>>& textureRegister();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_SRC_BUILDERS_TEXTUREBUILDER_H_ */
