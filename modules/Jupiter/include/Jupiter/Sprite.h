/*
 * Sprite.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <Jupiter/Common.h>
#include <Jupiter/Texture.h>
#include <Jupiter/ISpriteLoader.h>

namespace jupiter
{

class Sprite
{
public:
    Sprite(std::shared_ptr<Texture> texture, ISpriteLoader::Ptr spriteLoader);
    virtual ~Sprite() = default;

    virtual std::shared_ptr<Texture> getTexture() const throw ();
    virtual const float* getVertex() const throw ();
    virtual uint32_t getVertexCount() const throw ();
    virtual glm::mat4& getModelMatrix() throw ();

    virtual ISpriteLoader::SpriteType getDrawType() const throw ();

private:
    std::shared_ptr<Texture> _texture;

//    std::shared_ptr<float> _vertex;
    std::vector<float> _vertex;

    uint32_t _vertexCount;
    glm::mat4 _modelMatrix;
    ISpriteLoader::SpriteType _type;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
