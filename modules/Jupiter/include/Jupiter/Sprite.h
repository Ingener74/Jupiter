/*
 * Sprite.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <memory>
#include "Jupiter/JupiterError.h"
#include "Jupiter/Node.h"
#include "Jupiter/Shader.h"
#include "Jupiter/Texture.h"
#include "Jupiter/Shape.h"

namespace jupiter {

class Sprite: public Node {
public:
    Sprite(const std::string& name);
    virtual ~Sprite() = default;

    Texture* getTexture() const;
    Shape* getShape() const;
    Shader* getProgram() const;

private:
    Texture* _texture = nullptr;
    Shape* _shape = nullptr;
    Shader* _program = nullptr;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
