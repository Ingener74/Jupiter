/*
 * Sprite.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <memory>
#include <Jupiter/JupiterError.h>
#include <Jupiter/Node.h>

namespace jupiter
{

class SpriteImpl;

class Sprite: public Node
{
public:
    Sprite(const std::string& sprite) throw (JupiterError);

private:
    std::shared_ptr<SpriteImpl> _impl;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
