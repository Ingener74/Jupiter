
namespace jupiter{

class JupiterError
{
public:
    JupiterError(const std::string& message);
    virtual ~JupiterError() throw ();

    virtual const char* what() const throw();
};

}