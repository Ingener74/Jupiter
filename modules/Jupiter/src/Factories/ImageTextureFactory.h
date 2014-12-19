/*
 * ImageTextureBuilder.h
 *
 *  Created on: Dec 15, 2014
 *      Author: pavel
 */

#ifndef IMAGETEXTUREBUILDER_H_
#define IMAGETEXTUREBUILDER_H_

#include <Jupiter/TextureBuilder.h>

namespace jupiter
{

class ImageTextureFactory: public TextureBuilder::Factory
{
public:
    ImageTextureFactory() = default;
    virtual ~ImageTextureFactory() = default;

    virtual std::shared_ptr<TextureImpl> create(const std::string& texture);
};

} /* namespace jupiter */

#endif /* IMAGETEXTUREBUILDER_H_ */
