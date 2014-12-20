
namespace jupiter
{

class Shape
{
public:
    enum class Type
    {
        Triangles, TriangleFan, TriangleStrip, LineStrip
    };

    Shape();
    Shape(const std::string&);
    Shape(const std::vector<float>& data, Type);
    virtual ~Shape();

    int32_t vertexCount() const;
    Type type() const;
};

}