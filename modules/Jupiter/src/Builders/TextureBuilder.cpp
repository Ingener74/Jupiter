/*
 * TextureBuilder.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include "TextureBuilder.h"

namespace jupiter
{

TextureBuilder::TextureBuilder()
{
}

TextureBuilder::~TextureBuilder()
{
}

std::shared_ptr<TextureImpl> TextureBuilder::create( const std::string& texture )
{
    std::string type, parameter;



    return Register()[ type ]->create(parameter);
}

void TextureBuilder::addFactory( std::string& type, std::shared_ptr<Factory> factory )
{
    Register()[ type ] = factory;
}

std::map<std::string, std::shared_ptr<TextureBuilder::Factory> >& TextureBuilder::Register()
{
    static std::map<std::string, std::shared_ptr<TextureBuilder::Factory> > reg;
    return reg;
}

} /* namespace jupiter */
