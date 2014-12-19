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
#include <Jupiter/Texture.h>
#include <Jupiter/Shape.h>

namespace jupiter
{

class Sprite: public Node
{
public:
    Sprite(const std::string& sprite) throw (JupiterError);

    const Texture& getTexture() const;
    const Shape& getShape() const;

private:
    Texture _texture;
    Shape _shape;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
