
namespace jupiter {

class JsonGame: public Game {
public:
    JsonGame(const std::string& fileName) throw (JupiterError);
    virtual ~JsonGame();
};

}
