#pragma once
#include <exception>

/*!
* Describe an global error
*/
class HttpError : public std::exception
{
};

/*!
* Describe a 403 error
*/
class Error403 : public HttpError
{
};

/*!
* Describe a 404 error
*/
class Error404 : public HttpError
{
};
