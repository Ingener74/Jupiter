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

class Shape
{
public:
    enum class Type
    {
        Triangles, TriangleFan, TriangleStrip, LineStrip
    };

    Shape() = default;
    Shape( const std::string& );
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
    Type _type = Type::TriangleStrip;

    static const int DATA_IN_ONE_VERTEX = 5;
};

} /* namespace jupiter */

#endif /* SHAPE_H_ */
