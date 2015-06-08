/*
 * Shape.h
 *
 *  Created on: Dec 16, 2014
 *      Author: pavel
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#ifdef SWIG
    namespace jupiter {
        #pragma SWIG nowarn=312
    }  // namespace jupiter
#else
    #include <map>
    #include <string>
    #include <vector>
    #include <cstdint>

    #include "Jupiter/VertexComponent.h"
#endif

#include "RCO.h"

namespace jupiter
{

/*
 * {
 *     "shaderUniforms":{
 *         "texture0":"",
 *         "model":"",
 *     },
 *     "shaderAttribs":[
 *         "attribVertex":3,
 *         "attribTexCoord":2,
 *         "attribColor":4
 *     ],
 *     "data":[
 *         0.f, 0.f, 0.f,   0.f, 0.f,   1.f, 1.f, 1.f, 1.f,
 *         0.f, 0.f, 0.f,   0.f, 0.f,   1.f, 1.f, 1.f, 1.f,
 *         0.f, 0.f, 0.f,   0.f, 0.f,   1.f, 1.f, 1.f, 1.f
 *     ]
 * }
 */

class Shape: public RCO
{
public:
    enum Type
    {
        TRIANGLES, TRIANGLE_FAN, TRIANGLE_STRIP, LINE_STRIP
    };

    Shape() = default;
    Shape(const std::vector<float>& data, Type type);
    virtual ~Shape() = default;

    uint32_t getVertexCount() const;
    uint32_t getStride() const;
    Type getType() const;

    const VertexComponent& getComponent(const std::string& name);

protected:
    std::vector<float> data;
//    GLuint vbo = 0;
    uint32_t vertexCount = 0, stride = 0;
    std::map<std::string, VertexComponent> components;
    Type type = TRIANGLE_STRIP;
};

} /* namespace jupiter */

#endif /* SHAPE_H_ */
