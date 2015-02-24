
namespace jupiter{

class Game
{
public:
    Game();
    virtual ~Game();

    virtual void draw();

    virtual void input();

    virtual int32_t getWidth() const;
    virtual int32_t getHeight() const;
};

}
