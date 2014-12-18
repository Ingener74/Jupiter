/*
 * Sprite.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <map>
#include <iostream>

#include <Jupiter/facade/Sprite.h>
#include <Jupiter/JupiterError.h>

#include <Jupiter/detail/SpriteBuilder.h>

namespace jupiter
{

using namespace std;

//Sprite::Sprite(shared_ptr<Texture> texture, std::shared_ptr<ISpriteLoader> spriteLoader) :
//        _texture(texture ? texture : throw JupiterError("invalid texture")),
//        _vertexCount(spriteLoader ? spriteLoader->getVertexCount() : throw JupiterError("bad vertex count")),
//        _type(spriteLoader ? spriteLoader->getSpriteType() : throw JupiterError("bad sprite type"))
//{
//    auto p = spriteLoader->getVertexes();
//    _vertex = {p, p + _vertexCount * 5};
//}
//
//std::shared_ptr<Texture> Sprite::getTexture() const
//{
//    return _texture;
//}
//
//const float* Sprite::getVertex() const
//{
//    return _vertex.data();
//}
//
//uint32_t Sprite::getVertexCount() const
//{
//    return _vertexCount;
//}
//
//const glm::mat4& Sprite::getModelMatrix() const
//{
//    return _modelMatrix;
//}
//
//void Sprite::setModelMatrix(const glm::mat4& m)
//{
//    _modelMatrix = m;
//}
//
//ISpriteLoader::SpriteType Sprite::getDrawType() const
//{
//    return _type;
//}

Sprite::Sprite(const std::string& sprite) throw (JupiterError) :
        _impl(SpriteBuilder::create(sprite))
{
    cout << __PRETTY_FUNCTION__ << " " << sprite << endl;
}

} /* namespace ndk_game */
