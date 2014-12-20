/*
 * Shape.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: pavel
 */

#include <Jupiter/Shape.h>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

Shape::Shape(const std::string& shape)
{
    throw JupiterError("not implemented");
}

Shape::Shape(const std::vector<float>& data, Type type) :
        _data(data), _type(type)
{
}

int32_t Shape::vertexCount() const
{
    return _data.size() / DATA_IN_ONE_VERTEX;
}

Shape::Type Shape::type() const
{
    return _type;
}

bool Shape::hasCoordinates() const
{
}

int8_t Shape::coordinatesSize() const
{
}

const float* Shape::coordinatesData() const
{
}

bool Shape::hasTextureCoordinates() const
{
}

int8_t Shape::textureCoordinatesSize() const
{
}

const float* Shape::textureCoordinatesData() const
{
}

bool Shape::hasColor() const
{
}

int8_t Shape::colorSize() const
{
}

const float* Shape::colorData() const
{
}

int8_t Shape::getStride() const
{
}

} /* namespace jupiter */
