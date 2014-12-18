
namespace jupiter{

class Game
{
public:
    Game();
    Game(const std::string& gameFile);
    virtual ~Game();

    void draw();

    void input();
};

}
