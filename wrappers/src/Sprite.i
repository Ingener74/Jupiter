
namespace jupiter{

class Sprite: public Node
{
public:
    Sprite(const std::string& name);
    virtual ~Sprite() = default;

    Texture* getTexture() const;
    Shape* getShape() const;
    Shader* getProgram() const;
};

}
