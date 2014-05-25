/*
 * Sprite.h
 *
 *  Created on: 25 мая 2014 г.
 *      Author: Admin
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <Engine/Common.h>

#include <Engine/Texture.h>

namespace ndk_game
{

class Sprite
{
public:
    using Ptr = std::shared_ptr<Sprite>;

    Sprite();
    virtual ~Sprite();

    virtual void draw();

private:
    Texture::Ptr _texture;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
