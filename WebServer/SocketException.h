#pragma once
#include <exception>
#include <string>

/*!
* Exception used for an I/O error on the socket
* Can be used if unable to create the socket, or
* listen on the given port
*/
class SocketException : public std::exception
{
public:
    /*!
    * Constructor. Indicate the called function which failed,
    * the reason (as string, if possible), and the error code.
    */
    SocketException(const std::string & function, const std::string & reason, const int code);

    /*!
    * Return the error description string
    */
    const char * what() const throw();

private:
    /*!
    * The error description string
    */
    std::string _what;
};
