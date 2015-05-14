/*
 * Sprite.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#ifdef SWIG
#else
    #include <memory>
#endif

#include "Jupiter/Node.h"

namespace jupiter {

class Shape;
class Texture;
class Shader;

class Sprite: virtual public Node {
public:
    Sprite() = default;
    virtual ~Sprite() = default;

    Texture* getTexture() const;
    Sprite* setTexture(Texture*);

    Shape* getShape() const;
    Sprite* setShape(Shape*);

    Shader* getProgram() const;
    Sprite* setProgram(Shader*);

    virtual Sprite* accept(NodeVisitor* nv);
private:
    Texture* _texture = nullptr;
    Shape*   _shape   = nullptr;
    Shader*  _program = nullptr;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
