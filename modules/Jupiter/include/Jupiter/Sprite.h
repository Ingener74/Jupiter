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
#include <Jupiter/Shader.h>
#include <Jupiter/Texture.h>
#include <Jupiter/Shape.h>

namespace jupiter
{

class Sprite: public Node
{
public:
//    Sprite(const std::string& sprite) throw (JupiterError);
    Sprite() = default;
    virtual ~Sprite() = default;

    const Texture& getTexture() const;
    const Shape& getShape() const;
    std::shared_ptr<Shader> getProgram() const;

private:
    Texture _texture;
    Shape _shape;
    std::shared_ptr<Shader> _program;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
