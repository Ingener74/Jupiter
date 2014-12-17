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

float Sprite::getRotationX() const
{
    return 0.f;
}

float Sprite::getRotationY() const
{
    return 0.f;
}

float Sprite::getRotationZ() const
{
    return 0.f;
}

Sprite& Sprite::setRotation(float x, float y, float z)
{
    return *this;
}

Sprite& Sprite::setRotationX(float float1)
{
    return *this;
}

Sprite& Sprite::setRotationY(float float1)
{
    return *this;
}

Sprite& Sprite::setRotationZ(float float1)
{
    return *this;
}

Sprite& Sprite::rotate(float x, float y, float z)
{
    return *this;
}

Sprite& Sprite::rotateX(float float1)
{
    return *this;
}

Sprite& Sprite::rotateY(float float1)
{
    return *this;
}

Sprite& Sprite::rotateZ(float float1)
{
    return *this;
}

float Sprite::getPositionX() const
{
    return 0.f;
}

float Sprite::getPositionY() const
{
    return 0.f;
}

float Sprite::getPositionZ() const
{
    return 0.f;
}

Sprite& Sprite::setPosition(float x, float y, float z)
{
    return *this;
}

Sprite& Sprite::setPositionX(float float1)
{
    return *this;
}

Sprite& Sprite::setPositionY(float float1)
{
    return *this;
}

Sprite& Sprite::setPositionZ(float float1)
{
    return *this;
}

Sprite& Sprite::translate(float x, float y, float z)
{
    return *this;
}

Sprite& Sprite::translateX(float float1)
{
    return *this;
}

Sprite& Sprite::translateY(float float1)
{
    return *this;
}

Sprite& Sprite::translateZ(float float1)
{
    return *this;
}

float Sprite::getScaleX() const
{
    return 0.f;
}

float Sprite::getScaleY() const
{
    return 0.f;
}

Sprite& Sprite::setScale(float x, float y)
{
    return *this;
}

Sprite& Sprite::setScaleX(float float1)
{
    return *this;
}

Sprite& Sprite::setScaleY(float float1)
{
    return *this;
}

Sprite& Sprite::scale(float x, float y)
{
    return *this;
}

Sprite& Sprite::scaleX(float float1)
{
    return *this;
}

Sprite& Sprite::scaleY(float float1)
{
    return *this;
}

bool Sprite::isVisible() const
{
    return 0.f;
}

Sprite& Sprite::setVisible(bool bool1)
{
    return *this;
}

} /* namespace ndk_game */
