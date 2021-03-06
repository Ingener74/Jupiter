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
    #include <json.hpp>
#endif

#include "Jupiter/Node.h"

namespace jupiter {

class Shape;
class Texture;
class Shader;

class Sprite: public Node {
public:
    Sprite(Texture* = nullptr, Shape* = nullptr, Shader* = nullptr);
    virtual ~Sprite() = default;

    Sprite(const Sprite&);
    virtual Sprite* clone();

    Texture* getTexture();
    Sprite* setTexture(Texture*);

    Shape* getShape();
    Sprite* setShape(Shape*);

    Shader* getProgram();
    Sprite* setProgram(Shader*);

    virtual Sprite* accept(NodeVisitor* nv);

    virtual nlohmann::json getJson() const;
    friend std::ostream& operator<<(std::ostream&, Sprite const&);

protected:
    Ref<Texture> _texture;
    Ref<Shape>   _shape;
    Ref<Shader>  _program;

    Sprite& operator=(const Sprite&) = default;
};

} /* namespace ndk_game */

#endif /* SPRITE_H_ */
