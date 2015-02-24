
namespace jupiter
{

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
};

}