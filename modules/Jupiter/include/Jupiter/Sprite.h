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
    Sprite() = default;
    virtual ~Sprite() = default;

    Texture* getTexture() const;
    Sprite* setTexture(Texture*);

    Shape* getShape() const;
    Sprite* setShape(Shape*);

    Shader* getProgram() const;
    Sprite* setProgram(Shader*);

private:
    Texture* texture = nullptr;
    Shape* shape = nullptr;
    Shader* program = nullptr;
};

inline Texture* Sprite::getTexture() const {
    return texture;
}

inline Sprite* Sprite::setTexture(Texture* texture) {
    Sprite::texture = texture;
    return this;
}

inline Shape* Sprite::getShape() const {
    return shape;
}

inline Sprite* Sprite::setShape(Shape* shape) {
    Sprite::shape = shape;
    return this;
}

inline Shader* Sprite::getProgram() const {
    return program;
}

inline Sprite* Sprite::setProgram(Shader* program) {
    Sprite::program = program;
    return this;
}

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
