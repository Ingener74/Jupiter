
namespace jupiter {

class LinuxFileFactory: public BufferFactory {
public:
    LinuxFileFactory();
    virtual ~LinuxFileFactory();

    virtual std::streambuf* create(const std::string& fileName);
};

}