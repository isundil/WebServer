#pragma once
#include <string>

/*!
* Main response to send to the client
*/
class ARootElement
{
public:
    /*!
    * Return the page content. Can be raw text or HTML result page
    */
    virtual const std::string getValue() = 0;

	virtual ~ARootElement() {};

    /*!
    * Return the page content length, described in bytes
    */
    virtual unsigned int length() = 0;
};
