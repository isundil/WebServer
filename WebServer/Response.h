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
    * set content-type (default value: `text/html; charset=utf-8`)
    */
    Response & setContentType(const std::string & contentType = "text/html; charset=utf-8");
    /*!
    * get content-type
    */
    const std::string getContentType() const;
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
    * The response body
    */
    ARootElement * root;
    /*!
    * the content-type
    */
    std::string contentType;
};
