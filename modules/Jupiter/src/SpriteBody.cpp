/*
 * SpriteBox2d.cpp
 *
 *  Created on: 23 мая 2015 г.
 *      Author: Pavel
 */

#include "Jupiter/Ref.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/SpriteBody.h"

namespace jupiter {

using namespace std;
using namespace nlohmann;

SpriteBody::SpriteBody() :
    Sprite(), Body() {
}

SpriteBody::SpriteBody(Physics* visitor, b2BodyDef bodyDef, PhysicsShape* shape) :
    Sprite(), Body(visitor, bodyDef, shape) {
}

SpriteBody::~SpriteBody() {
}

SpriteBody::SpriteBody(const SpriteBody& sprite){
    clone(const_cast<SpriteBody*>(&sprite));
}

SpriteBody* SpriteBody::clone(SpriteBody* node) {
    Ref<SpriteBody>{node};
    jassert(node, "node is invalid");
    *this = *node;
    Sprite::clone(node);
    Body::clone(node);
    return this;
}

SpriteBody* SpriteBody::accept(NodeVisitor* nv) {
    Body::accept(nv);
    Sprite::accept(nv);
    return this;
}

json SpriteBody::getJson() const {
    return json{
        {
            "SpriteBody", {
                { "Base", {
                    Sprite::getJson(),
                    Body::getJson() } }
            }
        }
    };
}

ostream& operator<<(ostream& out, SpriteBody const& r) {
    return out << setw(4) << r.getJson();
}

} /* namespace jupiter */
