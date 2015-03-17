/*
 * Shape.h
 *
 *  Created on: Dec 16, 2014
 *      Author: pavel
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include <string>
#include <vector>
#include <cstdint>

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

class Shape
{
public:
    enum Type
    {
        TRIANGLES, TRIANGLE_FAN, TRIANGLE_STRIP, LINE_STRIP
    };

    Shape() = default;
    Shape( const std::vector<float>& data, Type );
    virtual ~Shape() = default;

    int32_t vertexCount() const;
    Type type() const;

    bool hasCoordinates() const;
    int8_t coordinatesSize() const;
    const float* coordinatesData() const;

    bool hasTextureCoordinates() const;
    int8_t textureCoordinatesSize() const;
    const float* textureCoordinatesData() const;

    bool hasColor() const;
    int8_t colorSize() const;
    const float* colorData() const;

    int8_t getStride() const;

private:
    std::vector<float> _data;
    Type _type = Type::TRIANGLE_STRIP;

    static const int DATA_IN_ONE_VERTEX = 5;
};

} /* namespace jupiter */

#endif /* SHAPE_H_ */
