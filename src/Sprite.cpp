/*
 * Sprite.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <Engine/Sprite.h>

namespace ndk_game
{

Sprite::Sprite(Texture::Ptr texture, ISpriteLoader::Ptr spriteLoader) :
        _texture(texture), _vertexCount(0),
         _type(spriteLoader->getSpriteType())
{
    _vertexCount = spriteLoader->getVertexCount();
    _vertex = std::shared_ptr<float>(new float[_vertexCount * 5], [](float * p)
    {
        delete [] p;
    });
    memcpy(_vertex.get(), spriteLoader->getVertexes(),
            _vertexCount * 5 * sizeof(float));
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

glm::mat4& Sprite::getModelMatrix() throw ()
{
    return _modelMatrix;
}

ISpriteLoader::SpriteType Sprite::getDrawType() const throw ()
{
    return _type;
}

} /* namespace ndk_game */

