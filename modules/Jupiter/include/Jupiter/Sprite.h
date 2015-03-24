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

#include "Jupiter/JupiterError.h"
#include "Jupiter/Node.h"
#include "Jupiter/Shader.h"
#include "Jupiter/Texture.h"
#include "Jupiter/Shape.h"

namespace jupiter {

class Sprite: public Node {
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
    Texture* texture = nullptr;
    Shape* shape = nullptr;
    Shader* program = nullptr;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
