/*
 * Sprite.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <Jupiter/Sprite.h>

namespace jupiter
{

using namespace std;

Sprite::Sprite(shared_ptr<Texture> texture, std::shared_ptr<ISpriteLoader> spriteLoader) :
        _texture(texture), _vertexCount(0), _type(spriteLoader->getSpriteType())
{
    _vertexCount = spriteLoader->getVertexCount();
//    _vertex = std::shared_ptr<float>(new float[_vertexCount * 5], [](float * p)
//    {
//        delete [] p;
//    });

    auto p = spriteLoader->getVertexes();
    _vertex = vector<float>
    { p, p + _vertexCount };

//    memcpy(_vertex.get(), spriteLoader->getVertexes(),
//            _vertexCount * 5 * sizeof(float));
}

std::shared_ptr<Texture> Sprite::getTexture() const
{
    return _texture;
}

const float* Sprite::getVertex() const
{
//    return _vertex.get();
    return _vertex.data();
}

uint32_t Sprite::getVertexCount() const
{
    return _vertexCount;
}

glm::mat4& Sprite::getModelMatrix()
{
    return _modelMatrix;
}

ISpriteLoader::SpriteType Sprite::getDrawType() const
{
    return _type;
}

} /* namespace ndk_game */

