/*
 * Sprite.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <Engine/Sprite.h>

namespace ndk_game
{

Sprite::Sprite(Texture::Ptr texture) :
        _texture(texture), _vertexCount(0)
{
}

Sprite::~Sprite()
{
}

Texture::Ptr Sprite::getTexture() const throw ()
{
    return _texture;
}

float* Sprite::getVertex() const throw ()
{
    return _vertex.get();
}

uint32_t Sprite::getVertexCount() const throw ()
{
    return _vertexCount;
}

const glm::mat4& Sprite::getModelMatrix() const throw ()
{
    return _modelMatrix;
}

} /* namespace ndk_game */
