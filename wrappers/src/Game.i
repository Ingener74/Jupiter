
namespace jupiter{

class Game
{
public:
    Game();
    virtual ~Game();

    virtual void draw();

    virtual void input();

    virtual int getWidth() const;
    virtual int getHeight() const;
};

}
