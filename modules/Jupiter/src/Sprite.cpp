/*
 * Sprite.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <map>
#include <iostream>

#include "Jupiter/NodeVisitor.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/Sprite.h"

namespace jupiter {

using namespace std;

Sprite* Sprite::clone(Sprite* sprite) {
    jassert(sprite, "sprite is invalid")
    *this = *sprite;
    return this;
}

Texture* Sprite::getTexture() const {
    jassert(_texture, "no texture")
    return _texture;
}

Sprite* Sprite::setTexture(Texture* texture) {
    jassert(texture, "texture is invalid")
    _texture = texture;
    return this;
}

Shape* Sprite::getShape() const {
    jassert(_shape, "no shape")
    return _shape;
}

Sprite* Sprite::setShape(Shape* shape) {
    jassert(shape, "shape is invalid")
    _shape = shape;
    return this;
}

Shader* Sprite::getProgram() const {
    jassert(_program, "no shader")
    return _program;
}

Sprite* Sprite::setProgram(Shader* program) {
    jassert(program, "shader is invalid")
    _program = program;
    return this;
}

Sprite* Sprite::accept(NodeVisitor* nv) {
    jassert(nv, "Sprite: visitor is nullptr");

    if (_visible) {

        nv->push(this);

        nv->visit(this);

        for (auto i : _nodes) {
            i->accept(nv);
        }

        nv->pop();
    }
    return this;
}

} /* namespace ndk_game */
