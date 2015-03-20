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
    std::vector<float> data;
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

inline bool Shape::hasCoordinates() const {
}

inline int8_t Shape::coordinatesSize() const {
}

inline const float* Shape::coordinatesData() const {
}

inline bool Shape::hasTextureCoordinates() const {
}

inline int8_t Shape::textureCoordinatesSize() const {
}

inline const float* Shape::textureCoordinatesData() const {
}

inline bool Shape::hasColor() const {
}

inline int8_t Shape::colorSize() const {
}

inline const float* Shape::colorData() const {
}

inline int8_t Shape::getStride() const {
}

} /* namespace jupiter */

#endif /* SHAPE_H_ */
