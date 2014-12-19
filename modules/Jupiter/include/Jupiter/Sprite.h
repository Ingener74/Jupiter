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
#include <Jupiter/ShaderProgram.h>

namespace jupiter
{

class Sprite: public Node
{
public:
    Sprite(const std::string& sprite) throw (JupiterError);

    const Texture& getTexture() const;
    const Shape& getShape() const;
    const ShaderProgram& getProgram() const;

private:
    Texture _texture;
    Shape _shape;
    ShaderProgram _program;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
