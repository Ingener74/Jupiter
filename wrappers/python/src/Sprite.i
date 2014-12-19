
namespace jupiter{

class Sprite: public Node
{
public:
    Sprite(const std::string& sprite) throw (JupiterError);
    
    const Texture& getTexture() const;
    const Shape& getShape() const;
};

}
