/*
 * Sprite.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <map>
#include <iostream>

#include <Jupiter/Sprite.h>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

using namespace std;

//Sprite::Sprite(const std::string& sprite) throw (JupiterError) :
//        Node(/*sprite*/), _texture(sprite), _shape(sprite), _program(sprite)
//{
//}

const Texture& Sprite::getTexture() const
{
    return _texture;
}

const Shape& Sprite::getShape() const
{
    return _shape;
}

shared_ptr<Shader> Sprite::getProgram() const
{
    return _program;
}

} /* namespace ndk_game */
