#include <sstream>
#include "SocketException.h"

SocketException::SocketException(const std::string & _function, const std::string & _reason, const int _code)
{
    std::stringstream ss;

    ss << "Function " << _function << " fail (" << _reason << "), code " << _code << std::endl;
    this->_what = ss.str();
}

const char * SocketException::what() const throw()
{
    return _what.c_str();
}
