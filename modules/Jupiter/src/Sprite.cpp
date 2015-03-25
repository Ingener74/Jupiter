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
    return texture;
}

Sprite* Sprite::setTexture(Texture* texture) {
    Sprite::texture = texture;
    return this;
}

Shape* Sprite::getShape() const {
    return shape;
}

Sprite* Sprite::setShape(Shape* shape) {
    Sprite::shape = shape;
    return this;
}

Shader* Sprite::getProgram() const {
    return program;
}

Sprite* Sprite::setProgram(Shader* program) {
    Sprite::program = program;
    return this;
}

Sprite* Sprite::accept(NodeVisitor* nv) {
    if (!nv)
        throw JupiterError("Node: visitor is nullptr");

    if (visible) {
        nv->visit(this);

        for (const auto& i : nodes) {
            i->accept(nv);
        }
    }

    return this;
}

} /* namespace ndk_game */
