#pragma once
#include <string>

class ARootElement;

/*!
* The response body string to be sent to the client
*/
class Response
{
public:
    Response();
    ~Response();

    /*!
    * Set the element to be sent
    * the element given MUST BE allocated using new()
    */
    Response & setElement(ARootElement *);

    /*!
    * The response size (in octets)
    */
    unsigned int length();

    /*!
    * The response body string to be sent to the client
    */
    std::string getValue();

    /*!
    * The response body string, as a RootElement
    */
    ARootElement * getElement();

private:

    /*!
    * he response body
    */
    ARootElement * root;
};
