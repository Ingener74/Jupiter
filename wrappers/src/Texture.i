
namespace jupiter
{

class Texture
{
public:
    Texture() = default;
    virtual ~Texture() = default;

    void bind() const;

    int getWidth() const;
    int getHeight() const;
};

}
