/*
 * Sprite.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <map>
#include <iostream>

#include "Jupiter/Sprite.h"
#include "Jupiter/JupiterError.h"

namespace jupiter {

using namespace std;

Sprite::Sprite(const std::string& name) :
    Node(name) {
}

Texture* Sprite::getTexture() const {
    return _texture;
}

Shape* Sprite::getShape() const {
    return _shape;
}

Shader* Sprite::getProgram() const {
    return _program;
}

} /* namespace ndk_game */
