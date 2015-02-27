
namespace jupiter {

class BufferFactory {
public:
    virtual ~BufferFactory() = default;
    virtual std::streambuf* create(const std::string& fileName) = 0;
};

class File{
public:
    File(const std::string& fileName);
    virtual ~File();

    std::istream& file();

    static void setBufferFactory(BufferFactory* = nullptr);
    static void setBase(const std::string& base);
};

}