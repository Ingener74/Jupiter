/*
 * ImageSpriteBuilder.h
 *
 *  Created on: Dec 7, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_IMAGESPRITEBUILDER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_IMAGESPRITEBUILDER_H_

#include <Jupiter/facade/Sprite.h>
#include <Jupiter/detail/SpriteBuilder.h>

namespace jupiter
{

class ImageSpriteBuilder: public SpriteBuilder::Factory
{
public:
    ImageSpriteBuilder();
    virtual ~ImageSpriteBuilder();

    virtual std::shared_ptr<SpriteImpl> create(const std::string& spriteId);
};

}  // namespace jupiter

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_IMAGESPRITEBUILDER_H_ */
