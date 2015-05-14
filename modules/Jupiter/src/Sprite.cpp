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

Texture* Sprite::getTexture() const {
    return _texture;
}

Sprite* Sprite::setTexture(Texture* texture) {
    _texture = texture;
    return this;
}

Shape* Sprite::getShape() const {
    return _shape;
}

Sprite* Sprite::setShape(Shape* shape) {
    _shape = shape;
    return this;
}

Shader* Sprite::getProgram() const {
    return _program;
}

Sprite* Sprite::setProgram(Shader* program) {
    _program = program;
    return this;
}

Sprite* Sprite::accept(NodeVisitor* nv) {
    JASSERT(nv, "Sprite: visitor is nullptr");

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
