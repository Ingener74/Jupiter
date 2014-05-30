/*
 * Sprite.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <Engine/Common.h>
#include <Engine/Texture.h>
#include <Engine/ISpriteLoader.h>

namespace ndk_game
{

class Sprite
{
public:
    using Ptr = std::shared_ptr<Sprite>;

    Sprite(Texture::Ptr texture, ISpriteLoader::Ptr spriteLoader);
    virtual ~Sprite();

    virtual Texture::Ptr getTexture() const throw ();
    virtual float* getVertex() const throw ();
    virtual uint32_t getVertexCount() const throw ();
    virtual glm::mat4& getModelMatrix() throw ();

    virtual ISpriteLoader::SpriteType getDrawType() const throw ();

private:
    Texture::Ptr _texture;
    std::shared_ptr<float> _vertex;
    uint32_t _vertexCount;
    glm::mat4 _modelMatrix;
    ISpriteLoader::SpriteType _type;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
