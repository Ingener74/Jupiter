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
    };

    static std::shared_ptr<TextureImpl> create( const std::string& texture );

    static void addFactory(std::string& type, std::shared_ptr<Factory>);

private:
    static std::map<std::string, std::shared_ptr<Factory>>& Register();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_SRC_BUILDERS_TEXTUREBUILDER_H_ */
