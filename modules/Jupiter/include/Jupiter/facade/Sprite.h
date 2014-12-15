/*
 * Sprite.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <cstdint>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <Jupiter/ISpriteLoader.h>

namespace jupiter
{

class Texture;
class SpriteImpl;

class Sprite
{
public:
    enum class Type
    {
        Triangles, TriangleFan, TriangleStrip, LineStrip
    };

    Sprite(const std::string& sprite);

    float getRotationX()const;
    float getRotationY()const;
    float getRotationZ()const;

    Sprite& setRotation(float x, float y, float z);
    Sprite& setRotationX(float);
    Sprite& setRotationY(float);
    Sprite& setRotationZ(float);

    Sprite& rotate(float x, float y, float z);
    Sprite& rotateX(float);
    Sprite& rotateY(float);
    Sprite& rotateZ(float);

    float getPositionX() const;
    float getPositionY() const;
    float getPositionZ() const;

    Sprite& setPosition(float x, float y, float z);
    Sprite& setPositionX(float);
    Sprite& setPositionY(float);
    Sprite& setPositionZ(float);

    Sprite& translate(float x, float y, float z);
    Sprite& translateX(float);
    Sprite& translateY(float);
    Sprite& translateZ(float);

    float getScaleX() const;
    float getScaleY() const;

    Sprite& setScale(float x, float y);
    Sprite& setScaleX(float);
    Sprite& setScaleY(float);

    Sprite& scale(float x, float y);
    Sprite& scaleX(float);
    Sprite& scaleY(float);

    bool isVisible() const;
    Sprite& setVisible(bool);

private:
    std::shared_ptr<SpriteImpl> _impl;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
