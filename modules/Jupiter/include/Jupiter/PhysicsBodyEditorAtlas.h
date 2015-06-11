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

std::ostream& operator<<(std::ostream& out, const b2Vec2& r);

struct PhysicsBodyEditorShape{
    PhysicsBodyEditorShape() = default;
    PhysicsBodyEditorShape(nlohmann::json rigidBody);

    std::string                        name;
    std::string                        imagePath;
    b2Vec2                             origin;
    std::vector<std::vector<b2Vec2>>   polygons;
    std::vector<Circle>                circles;

    friend std::ostream& operator<<(std::ostream& out, const PhysicsBodyEditorShape& r);
};

class PhysicsBodyEditorAtlas {
public:
    PhysicsBodyEditorAtlas(File*);
    virtual ~PhysicsBodyEditorAtlas();

    PhysicsBodyEditorShape getShape(std::string const& name);

private:
    std::map<std::string, PhysicsBodyEditorShape> _shapes;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_PHYSICSBODYEDITORATLAS_H_ */
