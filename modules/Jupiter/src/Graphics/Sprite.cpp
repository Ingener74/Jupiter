/*
 * Sprite.cpp
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#include <map>
#include <Jupiter/facade/Sprite.h>
#include <Jupiter/JupiterError.h>

#include <Jupiter/detail/SpriteBuilder.h>

namespace jupiter
{

using namespace std;

Sprite::Sprite(const std::string& sprite) :
        _impl(SpriteBuilder::create(sprite))
{
}

Sprite::Sprite(shared_ptr<Texture> texture, std::shared_ptr<ISpriteLoader> spriteLoader) :
        _texture(texture ? texture : throw JupiterError("invalid texture")),
        _vertexCount(spriteLoader ? spriteLoader->getVertexCount() : throw JupiterError("bad vertex count")),
        _type(spriteLoader ? spriteLoader->getSpriteType() : throw JupiterError("bad sprite type"))
{
    auto p = spriteLoader->getVertexes();
    _vertex = {p, p + _vertexCount * 5};
}

std::shared_ptr<Texture> Sprite::getTexture() const
{
    return _texture;
}

const float* Sprite::getVertex() const
{
    return _vertex.data();
}

uint32_t Sprite::getVertexCount() const
{
    return _vertexCount;
}

const glm::mat4& Sprite::getModelMatrix() const
{
    return _modelMatrix;
}

void jupiter::Sprite::setModelMatrix(const glm::mat4& m)
{
    _modelMatrix = m;
}

ISpriteLoader::SpriteType Sprite::getDrawType() const
{
    return _type;
}

float jupiter::Sprite::getRotationX() const
{
}

float jupiter::Sprite::getRotationY() const
{
}

float jupiter::Sprite::getRotationZ() const
{
}

Sprite& jupiter::Sprite::setRotation( float x, float y, float z )
{
    return *this;
}

Sprite& jupiter::Sprite::setRotationX( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::setRotationY( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::setRotationZ( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::rotate( float x, float y, float z )
{
    return *this;
}

Sprite& jupiter::Sprite::rotateX( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::rotateY( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::rotateZ( float float1 )
{
    return *this;
}

float jupiter::Sprite::getPositionX() const
{
}

float jupiter::Sprite::getPositionY() const
{
}

float jupiter::Sprite::getPositionZ() const
{
}

Sprite& jupiter::Sprite::setPosition( float x, float y, float z )
{
    return *this;
}

Sprite& jupiter::Sprite::setPositionX( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::setPositionY( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::setPositionZ( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::translate( float x, float y, float z )
{
    return *this;
}

Sprite& jupiter::Sprite::translateX( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::translateY( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::translateZ( float float1 )
{
    return *this;
}

float jupiter::Sprite::getScaleX() const
{
}

float jupiter::Sprite::getScaleY() const
{
}

Sprite& jupiter::Sprite::setScale( float x, float y )
{
    return *this;
}

Sprite& jupiter::Sprite::setScaleX( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::setScaleY( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::scale( float x, float y )
{
    return *this;
}

Sprite& jupiter::Sprite::scaleX( float float1 )
{
    return *this;
}

Sprite& jupiter::Sprite::scaleY( float float1 )
{
    return *this;
}

bool jupiter::Sprite::isVisible() const
{
}

Sprite& jupiter::Sprite::setVisible( bool bool1 )
{
    return *this;
}

} /* namespace ndk_game */
