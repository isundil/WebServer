#pragma once
#include <sstream>
#include "ARootElement.h"

/*!
* If the page's content is not an html page, you SHOULD use RawRootElement
* This permit you to set directly the content of the page.
*/
class RawRootElement : public ARootElement
{
public:
    /*!
    * Create an empty new page
    */
    RawRootElement();

    /*!
    * Create a new page containing "elem"
    */
    template <class T>
    RawRootElement(T elem)
    {
        value << elem;
    }

    virtual ~RawRootElement();

    /*!
    * return the string value of the page
    */
    virtual const std::string getValue();
    /*!
    * return the page length, to be sent in the http header
    */
    virtual unsigned int length();
    
    /*!
    * Add element e to the end of result
    */
    template <class T>
    RawRootElement & operator<<(T e)
    {
        value << e;
        return *this;
    }

private:
    /*!
    * contains the page's content
    */
    std::stringstream value;
};
