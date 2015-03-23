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
#endif

namespace jupiter
{

struct Elem {
    union {
        struct {
            float x, y, z;
            union {
                struct {
                    float tx, ty;
                };
                struct {
                    float r, g, b, a;
                };
            };
        };
    };
};


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

class VertexComponent {
public:
    VertexComponent(uint32_t size = 0, float* offset = nullptr) :
        size(size), offset(offset) {
    }
    virtual ~VertexComponent() {
    }

    uint32_t getSize() const {
        return 0;
    }

    const float* getOffset() const {
        return nullptr;
    }

private:
    uint32_t size = 0;
    float* offset = nullptr;
};

class Shape
{
public:
    enum Type
    {
        TRIANGLES, TRIANGLE_FAN, TRIANGLE_STRIP, LINE_STRIP
    };

    Shape() = default;
    Shape(const std::vector<float>& data, Type type);
    virtual ~Shape() = default;

    int32_t getVertexCount() const;
    Type getType() const;
    int8_t getStride() const;

    const VertexComponent& getComponent(const std::string& name);

private:
    std::vector<float> data;
    std::map<std::string, VertexComponent> components;
    Type type = Type::TRIANGLE_STRIP;

    static const int DATA_IN_ONE_VERTEX = 5;
};

inline Shape::Shape(const std::vector<float>& data, Type type) :
    data(data), type(type) {
}

inline int32_t Shape::getVertexCount() const {
    return data.size() / DATA_IN_ONE_VERTEX;
}

inline Shape::Type Shape::getType() const {
    return Shape::type;
}

inline int8_t Shape::getStride() const {
}

inline const VertexComponent& Shape::getComponent(const std::string& name) {
    return components [ name ];
}

} /* namespace jupiter */

#endif /* SHAPE_H_ */
