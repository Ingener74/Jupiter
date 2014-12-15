/*
 * SpriteImpl.h
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_SRC_SPRITEIMPL_H_
#define MODULES_JUPITER_SRC_SPRITEIMPL_H_

#include <vector>

#include <glm/glm.hpp>

#include <Jupiter/Texture.h>
#include <Jupiter/facade/Sprite.h>

namespace jupiter
{

class SpriteImpl
{
public:
    SpriteImpl();
    virtual ~SpriteImpl();

//        Sprite() = default;
//    Sprite(std::shared_ptr<Texture> texture, std::shared_ptr<ISpriteLoader> spriteLoader);
//    virtual ~Sprite() = default;
//
//    virtual std::shared_ptr<Texture> getTexture() const;
//    virtual const float* getVertex() const;
//    virtual uint32_t getVertexCount() const;
//
//    virtual const glm::mat4& getModelMatrix() const;
//    virtual void setModelMatrix(const glm::mat4&);
//
//    virtual ISpriteLoader::SpriteType getDrawType() const;

    Texture _texture;

    std::vector<float> _vertex;

    uint32_t _vertexCount = 0;
    glm::mat4 _modelMatrix;
    Sprite::Type _type = Sprite::Type::TriangleStrip;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_SRC_SPRITEIMPL_H_ */
