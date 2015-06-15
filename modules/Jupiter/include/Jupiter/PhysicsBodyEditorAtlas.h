/*
 * PhysicsBodyEditorAtlas.h
 *
 *  Created on: Jun 11, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_PHYSICSBODYEDITORATLAS_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_PHYSICSBODYEDITORATLAS_H_

#ifdef SWIG
#else
    #include <json.hpp>

    #include <Box2D/Box2D.h>
#endif

#include "RCO.h"

namespace jupiter {

class File;

struct Circle {
    Circle(b2Vec2 center, float radius);
    b2Vec2 center;
    float radius;
};

std::ostream& operator<<(std::ostream&, const b2Vec2&);

struct PhysicsBodyEditorShape{
    PhysicsBodyEditorShape() = default;
    PhysicsBodyEditorShape(nlohmann::json rigidBody);

    std::string                        name;
    std::string                        imagePath;
    b2Vec2                             origin;
    std::vector<std::vector<b2Vec2>>   polygons;
    std::vector<Circle>                circles;

    nlohmann::json getJson() const;
    friend std::ostream& operator<<(std::ostream&, const PhysicsBodyEditorShape&);
};

class PhysicsBodyEditorAtlas {
public:
    PhysicsBodyEditorAtlas(File*);
    virtual ~PhysicsBodyEditorAtlas();

    PhysicsBodyEditorShape getShape(std::string const& name);

    nlohmann::json getJson() const;
    friend std::ostream& operator<<(std::ostream&, const PhysicsBodyEditorAtlas&);

private:
    std::map<std::string, PhysicsBodyEditorShape> _shapes;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_PHYSICSBODYEDITORATLAS_H_ */
