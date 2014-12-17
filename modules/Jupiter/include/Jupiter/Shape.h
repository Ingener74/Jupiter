/*
 * Shape.h
 *
 *  Created on: Dec 16, 2014
 *      Author: pavel
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#ifndef SWIG
#include <vector>
#include <cstdint>
#endif

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
    Shape(const std::vector<float>& data);
    virtual ~Shape() = default;

    int32_t vertexCount() const;
    const float* vertexData() const;
    Type type() const;

#ifndef SWIG

private:
    std::vector<float> _data; // {{{x, y, z}, {tx, ty}}, ...} size = _vertexCount * 5
    Type _type = Type::TriangleStrip;
    static const int DATA_IN_ONE_VERTEX = 5;

#endif
};

} /* namespace jupiter */

#endif /* SHAPE_H_ */
