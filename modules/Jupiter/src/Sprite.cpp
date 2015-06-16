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
using namespace nlohmann;

Sprite::Sprite(Texture* texture, Shape* shape, Shader* program) :
    _texture(texture), _shape(shape), _program(program) {
}

Sprite::Sprite(const Sprite& sprite) {
    clone(const_cast<Sprite*>(&sprite));
}

Sprite* Sprite::clone(Sprite* sprite) {
    Ref<Sprite> { sprite };

    jassert(sprite, "sprite is invalid");
    *this = *sprite;
    return this;
}

Texture* Sprite::getTexture() {
    jassert(_texture, "no texture");
    return _texture.get();
}

Sprite* Sprite::setTexture(Texture* texture) {
    jassert(texture, "texture is invalid");
    _texture = texture;
    return this;
}

Shape* Sprite::getShape() {
    jassert(_shape, "no shape");
    return _shape.get();
}

Sprite* Sprite::setShape(Shape* shape) {
    jassert(shape, "shape is invalid");
    _shape = shape;
    return this;
}

Shader* Sprite::getProgram() {
    jassert(_program, "no shader");
    return _program.get();
}

Sprite* Sprite::setProgram(Shader* program) {
    jassert(program, "shader is invalid");
    _program = program;
    return this;
}

Sprite* Sprite::accept(NodeVisitor* nv) {
    jassert(nv, "Sprite: visitor is nullptr");
    if (_visible) {
        nv->push(this);
        nv->visit(this);
        for (auto i : _nodes) {
            jassert(i, "node is invalid");
            i->accept(nv);
        }
        nv->pop(this);
    }
    return this;
}

json Sprite::getJson() const {
    return json {
        {
            "Sprite", {
                {"Base", {Node::getJson()} },
            }
        },
    };
}

ostream& operator<<(ostream& out, Sprite const& r) {
    return out << setw(4) << r.getJson();
}

} /* namespace ndk_game */
