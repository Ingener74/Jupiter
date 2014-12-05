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

class Sprite
{
public:
    Sprite(std::shared_ptr<Texture> texture, std::shared_ptr<ISpriteLoader> spriteLoader);
    virtual ~Sprite() = default;

    virtual std::shared_ptr<Texture> getTexture() const;
    virtual const float* getVertex() const;
    virtual uint32_t getVertexCount() const;
    virtual const glm::mat4& getModelMatrix() const;

    virtual ISpriteLoader::SpriteType getDrawType() const;

private:
    std::shared_ptr<Texture> _texture;

    std::vector<float> _vertex;

    uint32_t _vertexCount;
    glm::mat4 _modelMatrix;
    ISpriteLoader::SpriteType _type;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
