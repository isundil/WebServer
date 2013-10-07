#pragma once
#include <exception>

class HttpError : public std::exception
{
};

class Error403 : public HttpError
{
};

class Error404 : public HttpError
{
};
