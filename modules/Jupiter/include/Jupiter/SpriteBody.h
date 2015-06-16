/*
 * SpriteBox2d.h
 *
 *  Created on: 23 мая 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_SPRITEBODY_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_SPRITEBODY_H_

#ifdef SWIG
#else
    #include <Box2D/Box2D.h>
    #include <json.hpp>
#endif

#include "Body.h"
#include "Sprite.h"

namespace jupiter {

class NodeVisitor;
class Physics;
class PhysicsShape;

class SpriteBody: public Sprite, public Body {
public:
    SpriteBody();
    SpriteBody(Physics*, b2BodyDef, PhysicsShape*);
    virtual ~SpriteBody();

    SpriteBody(const SpriteBody&);
    virtual SpriteBody* clone(SpriteBody*);

    virtual SpriteBody* accept(NodeVisitor*);

    virtual nlohmann::json getJson() const;
    friend std::ostream& operator<<(std::ostream&, SpriteBody const&);

private:
    SpriteBody& operator=(const SpriteBody&) = default;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_SPRITEBODY_H_ */
