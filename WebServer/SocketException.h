#include <exception>
#include <string>

class SocketException : public std::exception
{
public:
    SocketException(const std::string & function, const std::string & reason, const int code);
    const char * what() const;

private:
    std::string _what;
};
