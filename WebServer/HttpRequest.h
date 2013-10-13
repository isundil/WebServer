#pragma once

#include <list>
#include <string>
#include "Cookie.h"

class InvalidRequestException : public std::exception
{
public:
    InvalidRequestException() {};
    const char * what() const throw()
    {
        return "Invalid request: invalid verb";
    }
};

class HttpRequest
{
public: //public nested
    enum reqtype
    {
        invalid,
        option,
        get,
        head,
        post,
        put,
        del,
        trace,
        connect
    };

public: //public methods
    HttpRequest();
    virtual ~HttpRequest();

    bool isValid() const;
    HttpRequest *addParam(const std::string & key, const std::string & value);
    HttpRequest *setRequest(const std::string & request);

    enum HttpRequest::reqtype getRequestType() const;
    const std::string getRequestParam() const;
    const std::string getRequestUrl() const;
    const std::string getHttpVersion() const;
    const std::string getHost() const;
	CookieManager * getCookies();

    void debug() const;

private: //privates method
	void evalCookies(const std::string &);

private: //private attributes
    std::list<std::pair<const std::string, const std::string> > paramList;
    std::pair<enum reqtype, std::string> request;
    std::string requestUrl;
    std::string httpVersion;
	CookieManager cookieMng;
};
