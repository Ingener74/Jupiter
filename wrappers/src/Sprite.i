
namespace jupiter{

class Sprite: public Node
{
public:
    Sprite() = default;
    virtual ~Sprite() = default;

    Texture* getTexture() const;
    Shape* getShape() const;
    Shader* getProgram() const;
};

}
