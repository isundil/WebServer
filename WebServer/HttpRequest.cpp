
#include <iostream>
#include <map>
#include "HttpRequest.h"
#include "Util.h"

static inline enum HttpRequest::reqtype getEnum(const std::string &input)
{
    std::map<std::string, const HttpRequest::reqtype> map;
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("OPTIONS", HttpRequest::reqtype::option));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("GET", HttpRequest::reqtype::get));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("HEAD", HttpRequest::reqtype::head));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("POST", HttpRequest::reqtype::post));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("PUT", HttpRequest::reqtype::put));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("DELETE", HttpRequest::reqtype::del));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("TRACE", HttpRequest::reqtype::trace));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("CONNECT", HttpRequest::reqtype::connect));
    return map[input];
}

HttpRequest::HttpRequest()
{
    request = std::pair<enum reqtype, std::string>(reqtype::invalid, "");
    httpVersion = "HTTP/1.1";
}

HttpRequest::~HttpRequest()
{}

HttpRequest *HttpRequest::addParam(const std::string & key, const std::string & value)
{
	if (key == "Cookie")
		evalCookies(value);
    paramList.insert(paramList.end(), std::pair<std::string, const std::string>(epur_begin_str(key.c_str()), epur_begin_str(value.c_str())));
    return this;
}

HttpRequest *HttpRequest::setRequest(const std::string & request)
{
    int pos = request.find(' ');
    std::string first = request.substr(0, pos);
    this->request = std::pair<enum reqtype, std::string>(getEnum(first), request.substr(pos +1));
    std::list<std::string> requestFields = string_split(this->request.second, ' ');
    for (auto i = requestFields.cbegin(); i != requestFields.cend(); i++)
    {
        if (i == requestFields.cbegin())
            requestUrl = url_decode(*(i));
        else
            httpVersion = *(i);
    }
    return this;
}

bool HttpRequest::isValid() const
{
    return request.first != HttpRequest::reqtype::invalid;
}

void HttpRequest::debug() const
{
    std::cout << "REQUEST: " << request.first << std::endl;
    for (auto i = paramList.cbegin(); i != paramList.cend(); i++)
        std::cout << (*i).first << " => " << (*i).second << std::endl;
}

const std::map<std::string, std::string> HttpRequest::getData() const
{
    return data;
}

unsigned int HttpRequest::getDataLength() const
{
    for (auto i = paramList.cbegin(); i != paramList.cend(); i++)
    {
        if ((*i).first == "Content-Length")
        {
            unsigned int result;
            std::stringstream ss((*i).second);
            ss >> result;
            return result;
        }
    }
    return 0;
}

void HttpRequest::parseData(const char *buffer)
{
    std::list<std::string> data = string_split(buffer, '&');
    size_t pos;

    for (auto i = data.cbegin(); i != data.cend(); i++)
    {
        pos = (*i).find("=");
        if (pos == (*i).npos)
            continue;
        this->data[(*i).substr(0, pos)] = url_decode((*i).substr(pos +1));
    }
}

const std::string HttpRequest::getHost() const
{
    for (auto i = paramList.cbegin(); i != paramList.cend(); i++)
        if ((*i).first == "Host")
            return (*i).second;
    return "";
}

HttpRequest::reqtype HttpRequest::getRequestType() const
{
    enum reqtype rt = request.first;
    return rt;
}

const std::string HttpRequest::getRequestParam() const
{
    return request.second;
}

const std::string HttpRequest::getRequestUrl() const
{
    return requestUrl;
}

const std::string HttpRequest::getHttpVersion() const
{
    return httpVersion;
}

void HttpRequest::evalCookies(const std::string &cookieString)
{
	std::list<std::string> cookies = string_split(cookieString, ';');
	for (auto i = cookies.cbegin(); i != cookies.cend(); i++)
	{
		size_t pos = (*i).find('=');
		std::string key = (*i).substr(1, pos -1);
		std::string value = (*i).substr(pos +1);
		cookieMng.setInitValue(key, value);
	}
}

CookieManager *HttpRequest::getCookies()
{
	return &cookieMng;
}
