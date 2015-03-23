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

class ShaderAttribute {
public:
    ShaderAttribute(int attribute) :
        attribute(attribute) {
        // glEnableAttribute(attribute)
    }
    virtual ~ShaderAttribute() {
        // glDisableAttribute(attribute);
    }

    ShaderAttribute* setData(class ShapeData* data) {
        // glSetDataToAttribute(data, stride, GL_FLOAT);
        return this;
    }

    friend std::ostream& operator<<(std::ostream& out, const ShaderAttribute& r) {
        return out << "attribute : " << attribute;
    }

private:
    int attribute = 0;
};

class ShapeData {
public:
    ShapeData() {
    }
    virtual ~ShapeData() {
    }

    const float* getData() const {
        return nullptr;
    }

    uint32_t getSize() const {
        return 0;
    }
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

    int32_t vertexCount() const;
    Shape::Type getType() const;

    int8_t getStride() const;

private:
    std::vector<float> data;
    std::
    Type type = Type::TRIANGLE_STRIP;

    static const int DATA_IN_ONE_VERTEX = 5;
};

inline Shape::Shape(const std::vector<float>& data, Type type) :
    data(data), type(type) {
}

inline int32_t Shape::vertexCount() const {
    return data.size() / DATA_IN_ONE_VERTEX;
}

inline Shape::Type Shape::getType() const {
    return Shape::type;
}

inline int8_t Shape::getStride() const {
}

} /* namespace jupiter */

#endif /* SHAPE_H_ */
